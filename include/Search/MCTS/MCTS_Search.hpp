#pragma once

#include <chrono>
#include <random>
#include <time.h>

#include "GameResult.hpp"
#include "GameState.hpp"
#include "MCTS_Node.hpp"
#include "MCTS_Tree.hpp"
#include "Move.hpp"

using namespace Search::MCTS;
using namespace Piranhas;

namespace Search::MCTS {
    class MCTS_Search {
        PlayerColor maximizingPlayerColor;

        MCTS_Node *Select(MCTS_Node *mctsNode);
        MCTS_Node *Expand(MCTS_Node *mctsNode);
        bool Simulate(const MCTS_Node *expandedNode);
        void Backpropagate(MCTS_Node *expandedNode, bool simulationResult);

    public:
        MCTS_Search(PlayerColor maximizingPlayerColor);
        Move GetNextMove(GameState currentGameState, int searchTimeInMs);
    };
} // namespace Search::MCTS