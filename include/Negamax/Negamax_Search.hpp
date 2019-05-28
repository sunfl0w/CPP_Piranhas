#pragma once

#include <chrono>
#include <random>
#include <time.h>
#include <math.h>

#include "GameResult.hpp"
#include "GameState.hpp"
#include "Move.hpp"
#include "EvaluatedGameState.hpp"
#include "Evaluator.hpp"

using namespace Piranhas;

namespace Search::Negamax {
    class Negamax_Search {
        PlayerColor maximizingPlayerColor;
        int maxSearchTimeInMs;
        std::chrono::high_resolution_clock::time_point searchStartTimePoint;

        std::vector<GameState> GetChildGameStatesSorted(GameState gameState) const;

    public:
        Negamax_Search(PlayerColor maximizingPlayerColor, int maxSearchTimeInMs);
        Move GetNextMove(GameState currentGameState);
        EvaluatedGameState RunNegamaxSearch(GameState gameState, int depth, float alpha, float beta, bool maximizing);
    };
} // namespace Search::Negamax