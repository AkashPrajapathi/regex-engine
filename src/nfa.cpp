#include "nfa.hpp"

namespace re::nfa
{
    NFA::NFA(std::shared_ptr<re::ast::ASTNode> _ast) : ast(_ast), count(0) {}

    // null closure
    void NFA::epsClosure(std::shared_ptr<State> s, std::set<std::shared_ptr<State>> &closure)
    {
        // If s presents in closure then return
        if (closure.count(s))
            return;

        // Otherwise insert to closure
        closure.insert(s);

        // Check for every reachable state
        for (auto s : s->next)
        {
            if (s->symbol == '\0')
            {
                this->epsClosure(s, closure);
            }
        }
    }

    // move to next state
    void NFA::move(char symbol, std::shared_ptr<State> currentState, std::set<std::shared_ptr<State>> &nextStates)
    {
        for (auto s : currentState->next)
        {
            if (s->symbol == symbol)
                nextStates.insert(s);
        }
    }

    // get final state if it is exist otherwise last state
    std::shared_ptr<State> NFA::findAcceptState(std::shared_ptr<State> state)
    {
        if (this->isFound)
            return state;

        this->visited.insert(state->id);

        for (auto s : state->next)
        {
            if (this->visited.count(s->id))
                continue;
            if (s->isAccept)
                this->isFound = true;
            return this->findAcceptState(s);
        }

        return state;
    }

    void NFA::createLiteralNFA(std::shared_ptr<re::ast::ASTNode> astNode)
    {
        auto s1 = std::make_shared<State>(this->count);
        this->count += 1;
        auto s2 = std::make_shared<State>(this->count, astNode->getValue(), true);
        this->count += 1;

        s1->next.push_back(s2);

        this->nfas.push_back(s1);
    }

    void NFA::createConcatNFA()
    {
        if (this->nfas.size() < 2)
            throw std::runtime_error("Two operand required");

        auto nfa1 = this->nfas[this->nfas.size() - 2];
        auto nfa2 = this->nfas[this->nfas.size() - 1];

        this->nfas.pop_back();
        this->nfas.pop_back();

        this->isFound = false;
        this->visited.clear();
        auto f1 = this->findAcceptState(nfa1);

        f1->isAccept = false;
        f1->next.push_back(nfa2);

        this->nfas.push_back(nfa1);
    }

    void NFA::createAlterationNFA()
    {
        if (this->nfas.size() < 2)
            throw std::runtime_error("Two operand required");

        auto newStart = std::make_shared<State>(this->count);
        this->count += 1;
        auto newFinal = std::make_shared<State>(this->count, '\0', true);
        this->count += 1;

        auto nfa1 = this->nfas[this->nfas.size() - 2];
        auto nfa2 = this->nfas[this->nfas.size() - 1];

        newStart->next.push_back(nfa1);
        newStart->next.push_back(nfa2);

        this->isFound = false;
        this->visited.clear();
        auto f1 = this->findAcceptState(nfa1);

        this->isFound = false;
        this->visited.clear();
        auto f2 = this->findAcceptState(nfa2);

        f1->isAccept = false;
        f2->isAccept = false;

        f1->next.push_back(newFinal);
        f2->next.push_back(newFinal);

        this->nfas.pop_back();
        this->nfas.pop_back();

        this->nfas.push_back(newStart);
    }

    void NFA::createStarNFA()
    {
        if (this->nfas.size() < 1)
            throw std::runtime_error("One operand required");

        auto s1 = std::make_shared<State>(this->count);
        this->count += 1;
        auto s2 = std::make_shared<State>(this->count, '\0', true);
        this->count += 1;

        auto subNFA = this->nfas[this->nfas.size() - 1];

        // Connect new start to sub nfa's start
        s1->next.push_back(subNFA);
        s1->next.push_back(s2);

        this->isFound = false;
        this->visited.clear();
        auto f1 = this->findAcceptState(subNFA);

        // Make final to non-final
        f1->isAccept = false;

        // Connect last state to start state of sub nfa
        f1->next.push_back(subNFA);

        // Connect last state of sub nfa to final state
        f1->next.push_back(s2);

        this->nfas.pop_back();
        this->nfas.push_back(s1);
    }

    void NFA::createPlusNFA()
    {
        if (this->nfas.size() < 1)
            throw std::runtime_error("One operand required");

        // Cache last sub NFA
        auto newStart = std::make_shared<State>(this->count);
        this->count += 1;
        auto newFinal = std::make_shared<State>(this->count, '\0', true);
        this->count += 1;

        auto s1 = this->nfas[this->nfas.size() - 1];

        this->isFound = false;
        this->visited.clear();
        auto f1 = this->findAcceptState(s1);

        // Make final to non-final
        f1->isAccept = false;

        // Connect last state to start state of sub nfa
        f1->next.push_back(s1);

        // Connect last state of sub nfa to final state
        f1->next.push_back(newFinal);

        // Connect to start state of sub nfa
        newStart->next.push_back(s1);

        // Remove last sun NFA
        this->nfas.pop_back();

        // Final NFA
        this->nfas.push_back(newStart);
    }

    void NFA::createOptionalQuantifierNFA()
    {
        if (this->nfas.size() < 1)
            throw std::runtime_error("One operand required");

        // Cache last sub NFA
        auto newStart = std::make_shared<State>(this->count);
        this->count += 1;
        auto newFinal = std::make_shared<State>(this->count, '\0', true);
        this->count += 1;

        auto s1 = this->nfas[this->nfas.size() - 1];

        this->isFound = false;
        this->visited.clear();
        auto f1 = this->findAcceptState(s1);

        // Make final to non-final
        f1->isAccept = false;

        // Connect sub nfa final state to new final state
        f1->next.push_back(newFinal);

        // Connect to start state of sub nfa
        newStart->next.push_back(s1);

        // Connect to new final state
        newStart->next.push_back(newFinal);

        // Remove last sun NFA
        this->nfas.pop_back();

        // Final NFA
        this->nfas.push_back(newStart);
    }

    // create nfa graph
    void NFA::createNFA(std::shared_ptr<re::ast::ASTNode> node)
    {
        for (auto child : node->getChildren())
            this->createNFA(child);

        if (node->getType() == AST_LITERAL)
            this->createLiteralNFA(node);

        else if (node->getType() == AST_CONCAT)
            this->createConcatNFA();

        else if (node->getType() == AST_ALTERNATION)
            this->createAlterationNFA();

        else if (node->getType() == AST_KLEEN_STAR)
            this->createStarNFA();

        else if (node->getType() == AST_KLEEN_PLUS)
            this->createPlusNFA();

        else if (node->getType() == AST_OPTIONAL_QUANTIFIER)
            this->createOptionalQuantifierNFA();
    }

    bool NFA::simulateNFA(const std::string &input)
    {
        // Create NFA graph
        this->createNFA(this->ast);

        // final NFA graph
        auto startState = this->nfas[0];

        // Step 0
        std::set<std::shared_ptr<State>> current;
        this->epsClosure(startState, current);

        // Step 1
        for (auto c : input)
        {
            std::set<std::shared_ptr<State>> next;
            for (auto s : current)
                this->move(c, s, next);

            current.clear();

            // Step 2
            for (auto s : next)
                this->epsClosure(s, current);
        }

        bool isAccept = false;
        for (auto s : current)
        {
            if (s->isAccept)
            {
                isAccept = true;
                break;
            }
        }

        return isAccept;
    }

} // namespace re::nfa
