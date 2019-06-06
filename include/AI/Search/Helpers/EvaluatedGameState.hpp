#pragma once

#include "Piranhas/GameState.hpp"

namespace AI::Search::Helpers {
    struct EvaluatedGameState {
        float eval;
        Piranhas::GameState gameState;

        EvaluatedGameState() {}

        EvaluatedGameState(Piranhas::GameState gameState, float eval) {
            this->eval = eval;
            this->gameState = gameState;
        }
    };
}