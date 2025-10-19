#include "lexer.hpp"

namespace re
{
    Lexer::Lexer(const std::string &pattern) : pattern(pattern), pos(0)
    {
        this->token.value = '\0';
        this->token.type = NULL_CHAR;
    }

    Token Lexer::current()
    {
        return this->token;
    }

    void Lexer::next()
    {
        if (this->pos > this->pattern.size() - 1)
        {
            this->token.value = '\0';
            this->token.type = EOT;
            return;
        }

        if (std::isalpha(this->pattern[this->pos]))
        {
            this->token.value = this->pattern[this->pos];
            this->token.type = LITERAL;
            this->pos++;
        }
        else if (this->pattern[this->pos] == '(')
        {
            this->token.value = this->pattern[this->pos];
            this->token.type = GROUP_START;
            this->pos++;
        }
        else if (this->pattern[this->pos] == ')')
        {
            this->token.value = this->pattern[this->pos];
            this->token.type = GROUP_END;
            this->pos++;
        }
        else if (this->pattern[this->pos] == '*')
        {
            this->token.value = this->pattern[this->pos];
            this->token.type = KLEEN_STAR;
            this->pos++;
        }
        else if (this->pattern[this->pos] == '+')
        {
            this->token.value = this->pattern[this->pos];
            this->token.type = KLEEN_PLUS;
            this->pos++;
        }
        else if (this->pattern[this->pos] == '|')
        {
            this->token.value = this->pattern[this->pos];
            this->token.type = ALTERATION;
            this->pos++;
        }
        else if (this->pattern[this->pos] == '?')
        {
            this->token.value = this->pattern[this->pos];
            this->token.type = OPTIONAL_QUANTIFIER;
            this->pos++;
        }
        else
        {
            std::stringstream err;
            err << "TokenError: unknown token "
                << this->pattern[this->pos];

            throw std::runtime_error(err.str());
        }
    }

    void Lexer::showTokens()
    {
        std::string type;
        this->next();

        while (this->current().type != EOT)
        {
            switch (this->current().type)
            {
            case LITERAL:
                type = "Literal";
                break;
            case GROUP_START:
                type = "Group Start";
                break;
            case GROUP_END:
                type = "Group End";
                break;
            case KLEEN_STAR:
                type = "Kleen Star";
                break;
            case KLEEN_PLUS:
                type = "Kleen Plus";
                break;
            case ALTERATION:
                type = "Alteration";
                break;
            case OPTIONAL_QUANTIFIER:
                type = "Optional Quantifier";
                break;
            case NULL_CHAR:
                type = "NULL CHAR";
                break;

            default:
                break;
            }

            std::cout << "Type: " << type << ", Value: " << this->current().value << "\n";

            this->next();
        }
    }

} // namespace re