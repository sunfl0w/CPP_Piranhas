#pragma once

#include <chrono>
#include <math.h>

#include "PlayerColor.hpp"
#include "GameState.hpp"
#include "EvaluatedGameState.hpp"

#include "Negamax_Search.hpp"

using namespace Piranhas;

namespace Search {
    class MoveSearch {
    private:
        int maxSearchTimeInMs;
        PlayerColor ownPlayerColor;
        int maxSearchDepth;
        std::chrono::high_resolution_clock::time_point searchStartTimePoint;

    public:
        MoveSearch(int maxSearchTimeInMs, int maxSearchDepth);

        Move SearchNextMove(GameState gameState, PlayerColor ownPlayerColor);
    };
} // namespace Search
