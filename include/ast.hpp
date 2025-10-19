#pragma once

#include <vector>
#include <memory>
#include "./node_type.hpp"

namespace re::ast
{
    class ASTNode
    {
        NodeType type;
        char value;
        std::vector<std::shared_ptr<ASTNode>> children;

    public:
        ASTNode(NodeType t, char value);

        NodeType getType() const;
        char getValue() const;

        void addChild(std::shared_ptr<ASTNode> child);
        const std::vector<std::shared_ptr<ASTNode>> &getChildren() const;
    };
} // namespace re::ast