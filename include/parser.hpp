#pragma once

#include "./lexer.hpp"
#include "./ast.hpp"

namespace re
{
    class Parser
    {
        Lexer lex;

    public:
        Parser(const Lexer lex);

        std::shared_ptr<re::ast::ASTNode> parse();

    private:
        void match(Type type);
        std::shared_ptr<re::ast::ASTNode> parseLiteral();
        std::shared_ptr<re::ast::ASTNode> parsePrimary();
        std::shared_ptr<re::ast::ASTNode> parseRepetition();
        std::shared_ptr<re::ast::ASTNode> parseConcatenation();
        std::shared_ptr<re::ast::ASTNode> parseAlteration();
        std::shared_ptr<re::ast::ASTNode> parseRegex();
    };
} // namespace re