#include "parser.hpp"

namespace re
{
    Parser::Parser(const Lexer lex) : lex(lex) {}

    std::shared_ptr<re::ast::ASTNode> Parser::parse()
    {
        this->lex.next();
        return this->parseRegex();
    }

    void Parser::match(Type type)
    {
        if (this->lex.current().type == type)
        {
            this->lex.next();
        }
        else
        {
            std::stringstream err;
            err << "ParserError: unexpected token "
                << this->lex.current().value;
            throw std::runtime_error(err.str());
        }
    }

    std::shared_ptr<re::ast::ASTNode> Parser::parseRegex()
    {
        auto regex = this->parseAlteration();
        this->match(EOT);
        return regex;
    }

    std::shared_ptr<re::ast::ASTNode> Parser::parseAlteration()
    {
        auto left = this->parseConcatenation();

        if (this->lex.current().type == ALTERATION)
        {
            this->match(ALTERATION);
            auto right = this->parseAlteration(); // recursively parse right side

            auto alter = std::make_shared<re::ast::ASTNode>(AST_ALTERNATION, '|');
            alter->addChild(left);
            alter->addChild(right);
            return alter;
        }

        return left;
    }

    std::shared_ptr<re::ast::ASTNode> Parser::parseConcatenation()
    {
        std::vector<std::shared_ptr<re::ast::ASTNode>> nodes;
        nodes.push_back(this->parseRepetition());

        while (this->lex.current().type == LITERAL || this->lex.current().type == GROUP_START)
        {
            nodes.push_back(this->parseRepetition());
        }

        if (nodes.size() == 1)
            return nodes[0]; // single repetition, no concat node needed

        auto concat = std::make_shared<re::ast::ASTNode>(AST_CONCAT, '.');
        for (auto &node : nodes)
            concat->addChild(node);

        return concat;
    }

    std::shared_ptr<re::ast::ASTNode> Parser::parseRepetition()
    {
        auto primary = this->parsePrimary();

        if (this->lex.current().type == KLEEN_STAR)
        {
            auto repeat = std::make_shared<re::ast::ASTNode>(AST_KLEEN_STAR, '*');
            repeat->addChild(primary);
            this->match(KLEEN_STAR);
            return repeat;
        }
        else if (this->lex.current().type == KLEEN_PLUS)
        {
            auto repeat = std::make_shared<re::ast::ASTNode>(AST_KLEEN_PLUS, '+');
            repeat->addChild(primary);
            this->match(KLEEN_PLUS);
            return repeat;
        }
        else if (this->lex.current().type == OPTIONAL_QUANTIFIER)
        {
            auto repeat = std::make_shared<re::ast::ASTNode>(AST_OPTIONAL_QUANTIFIER, '?');
            repeat->addChild(primary);
            this->match(OPTIONAL_QUANTIFIER);
            return repeat;
        }

        return primary;
    }

    std::shared_ptr<re::ast::ASTNode> Parser::parseLiteral()
    {
        auto node = std::make_shared<re::ast::ASTNode>(AST_LITERAL, this->lex.current().value);
        this->match(LITERAL);
        return node;
    }

    std::shared_ptr<re::ast::ASTNode> Parser::parsePrimary()
    {
        if (this->lex.current().type == LITERAL)
            return this->parseLiteral();

        this->match(GROUP_START);
        auto group = std::make_shared<re::ast::ASTNode>(AST_GROUP, 'G');
        group->addChild(this->parseAlteration());
        this->match(GROUP_END);
        return group;
    }

} // namespace re