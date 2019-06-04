#pragma once 

#include "TranspositionFlag.hpp"
#include "Move.hpp"

namespace Client::Storage {
    struct Transposition {
        float eval;
        unsigned int depth;
        TranspositionFlag flag;
        Piranhas::Move hashMove;

        Transposition(float eval, unsigned int depth, TranspositionFlag transpositionFlag);
    };
}