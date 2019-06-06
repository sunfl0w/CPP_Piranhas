#pragma once

#include <chrono>
#include <random>
#include <time.h>

#include "Piranhas/GameResult.hpp"
#include "Piranhas/GameState.hpp"
#include "AI/Search/SearchAlgorithms/MCTS/MCTS_Node.hpp"
#include "Piranhas/Move.hpp"

namespace AI::Search::SearchAlgorithms::MCTS {
    class MCTS_Search {
        Piranhas::PlayerColor maximizingPlayerColor;

        MCTS_Node *Select(MCTS_Node *mctsNode);
        MCTS_Node *Expand(MCTS_Node *mctsNode);
        bool Simulate(const MCTS_Node *expandedNode);
        void Backpropagate(MCTS_Node *expandedNode, bool simulationResult);

    public:
        MCTS_Search(Piranhas::PlayerColor maximizingPlayerColor);
        Piranhas::Move GetNextMove(Piranhas::GameState currentGameState, int searchTimeInMs);
    };
} // namespace Search::MCTS