#pragma once

#include "GameState.hpp"

using namespace Piranhas;

namespace Search::Evaluation {
    class Evaluator {
    private:
        Evaluator();

    public:
        static float EvaluateGameState(GameState gameState, PlayerColor maximizingPlayerColor, bool maximizing);
    };
} // namespace Search::Evaluation