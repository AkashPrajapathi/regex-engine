#include <sstream>
#include <stdexcept>
#include <iostream>

#include "./token.hpp"

namespace re
{
    class Lexer
    {
        std::string pattern;
        int pos;
        Token token;

    public:
        Lexer(const std::string &pattern);
        Token current();
        void next();
        void showTokens();

    private:
        // void parseLiteral();
    };
}