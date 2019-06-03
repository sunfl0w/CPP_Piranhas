#pragma once

#include <vector>
#include <math.h>

#include "GameState.hpp"

using namespace Piranhas;

namespace Search::MCTS {
    struct MCTS_Node {
        int visits = 0;
        int wins = 0;

        GameState gameState;

        MCTS_Node* parentNode;
        std::vector<MCTS_Node*> childNodes;

        MCTS_Node(const GameState &gameState, MCTS_Node* parentNode);

        void PopulateChildNodes();

        float UCB(float explorationFactor) const;

        const bool IsParentNull() const;
        const bool IsFullyExpanded() const;

        MCTS_Node *GetNextUnvisitedChildNode();
        MCTS_Node *GetBestChildNode();
        MCTS_Node *GetBestChildNodeUCB();
    };
}