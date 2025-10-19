#pragma once

#include <vector>
#include <memory>

namespace re::nfa
{
    struct State
    {
        int id;
        char symbol;
        std::vector<std::shared_ptr<State>> next;
        bool isAccept;

        State(int _id, char _symbol = '\0', bool _isAccept = false) : id(_id), symbol(_symbol), isAccept(_isAccept) {}
    };
} // namespace re::nfa
