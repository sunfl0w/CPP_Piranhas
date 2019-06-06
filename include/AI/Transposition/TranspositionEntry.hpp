#pragma once 

#include "AI/Transposition/TranspositionFlag.hpp"
#include "Piranhas/Move.hpp"

namespace AI::Transposition {
    struct TranspositionEntry {
        float eval;
        unsigned int depth;
        TranspositionFlag flag;
        Piranhas::Move hashMove;

        TranspositionEntry(float eval, unsigned int depth, TranspositionFlag transpositionFlag, Piranhas::Move hashMove);
    };
}