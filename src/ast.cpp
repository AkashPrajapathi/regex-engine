#include "ast.hpp"

namespace re::ast
{
    ASTNode::ASTNode(NodeType t, char value) : type(t), value(value) {}

    NodeType ASTNode::getType() const
    {
        return this->type;
    }

    char ASTNode::getValue() const
    {
        return this->value;
    }

    // Adds a child node to the current AST node
    void ASTNode::addChild(std::shared_ptr<ASTNode> child)
    {
        this->children.push_back(child);
    }

    // Returns the children of the current AST node
    const std::vector<std::shared_ptr<ASTNode>> &ASTNode::getChildren() const
    {
        return this->children;
    }
} // namespace re::ast