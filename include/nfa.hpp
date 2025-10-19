#pragma once

#include <set>
#include <string>
#include <iostream>

#include "./node.hpp"
#include "./ast.hpp"

namespace re::nfa
{
    class NFA
    {
        std::shared_ptr<re::ast::ASTNode> ast;
        int count;

        // Helper member variable
        std::vector<std::shared_ptr<State>> nfas;
        bool isFound = false;
        std::set<int> visited;

    public:
        NFA(std::shared_ptr<re::ast::ASTNode> _ast);

        bool simulateNFA(const std::string &input);

    private:
        // null closure
        void epsClosure(std::shared_ptr<State> s, std::set<std::shared_ptr<State>> &closure);

        // move to next state
        void move(char symbol, std::shared_ptr<State> currentState, std::set<std::shared_ptr<State>> &nextStates);

        // get final state if it is exist otherwise last state
        std::shared_ptr<State> findAcceptState(std::shared_ptr<State> state);

        // create nfa graph
        void createNFA(std::shared_ptr<re::ast::ASTNode> ast);

        // create NFAs
        void createLiteralNFA(std::shared_ptr<re::ast::ASTNode> astNode);
        void createConcatNFA();
        void createAlterationNFA();
        void createStarNFA();
        void createPlusNFA();
        void createOptionalQuantifierNFA();
    };
} // namespace re::nfa
