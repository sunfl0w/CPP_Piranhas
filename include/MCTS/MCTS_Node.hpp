#pragma once

#include <vector>

#include "UCB.hpp"

using namespace Search::MCTS;

namespace Search::MCTS {
    struct MCTS_Node {
        int visits;
        int wins;

        GameState gameState;

        MCTS_Node* parentNode;
        std::vector<MCTS_Node> childNodes;

        const bool IsParentNull() const;
        const bool IsFullyExpanded() const;

        MCTS_Node GetNextUnvisitedChildNode() const;
        MCTS_Node GetBestChildNode() const;
    };
}