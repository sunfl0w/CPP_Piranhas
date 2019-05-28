#pragma once

#include "Move.hpp"

using namespace Piranhas;

namespace Search::Negamax {
    struct EvaluatedMove {
        float eval;
        Move move;

        EvaluatedMove(Move move, float eval) {
            this->eval = eval;
            this->move = move;
        }
    };
}