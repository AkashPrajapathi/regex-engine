#pragma once

enum NodeType
{
    AST_LITERAL,
    AST_ALTERNATION,
    AST_KLEEN_STAR,
    AST_KLEEN_PLUS,
    AST_OPTIONAL_QUANTIFIER,
    AST_GROUP,
    AST_CONCAT
};