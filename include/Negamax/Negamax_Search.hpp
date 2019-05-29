#pragma once

#include <chrono>
#include <random>
#include <time.h>
#include <math.h>
#include <algorithm>

#include "GameResult.hpp"
#include "GameState.hpp"
#include "Move.hpp"
#include "EvaluatedGameState.hpp"
#include "EvaluatedMove.hpp"
#include "Evaluator.hpp"

using namespace Piranhas;

namespace Search::Negamax {
    class Negamax_Search {
        PlayerColor ownPlayerColor;
        int maxSearchTimeInMs;
        std::chrono::high_resolution_clock::time_point searchStartTimePoint;

        std::vector<GameState> GetChildGameStatesSorted(const GameState &gameState, PlayerColor maximizingPlayerColor) const;
        std::vector<Move> GetPossibleMovesSorted(const GameState &gameState, const std::vector<Move> &possibleMoves, PlayerColor maximizingPlayerColor) const;

    public:
        Negamax_Search(PlayerColor ownPlayerColor, std::chrono::high_resolution_clock::time_point searchStartTimePoint, int maxSearchTimeInMs);
        EvaluatedGameState Negamax(const GameState &gameState, int depth, float alpha, float beta, bool maximizing);
    };
} // namespace Search::Negamax