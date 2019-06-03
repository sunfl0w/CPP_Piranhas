#pragma once

#include "GameState.hpp"

using namespace Piranhas;

namespace Search::Helpers {
    struct EvaluatedGameState {
        float eval;
        GameState gameState;

        EvaluatedGameState() {}

        EvaluatedGameState(GameState gameState, float eval) {
            this->eval = eval;
            this->gameState = gameState;
        }
    };
}