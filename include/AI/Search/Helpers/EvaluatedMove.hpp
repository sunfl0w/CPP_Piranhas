#pragma once

#include "Piranhas/Move.hpp"

namespace AI::Search::Helpers {
    struct EvaluatedMove {
        float eval;
        Piranhas::Move move;

        EvaluatedMove(Piranhas::Move move, float eval) {
            this->eval = eval;
            this->move = move;
        }
    };
}