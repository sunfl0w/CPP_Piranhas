#pragma once

#include "MCTS_Node.hpp"
#include "MCTS_Tree.hpp"
#include "GameState.hpp"
#include "Move.hpp"

using namespace Search::MCTS;
using namespace Piranhas;

namespace Search::MCTS {
    class MCTS_Search {
        MCTS_Node Select(const MCTS_Node &mctsNode);
        MCTS_Node Expand(const MCTS_Node &mctsNode);
        bool Simulate(const MCTS_Node &expandedNode);
        void Backpropagate(MCTS_Node &terminalNode);
        public:
        Move GetNextMove(GameState currentGameState);
    };
}