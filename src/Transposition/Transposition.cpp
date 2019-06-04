#include "Transposition.hpp"

using namespace Client::Storage;

Transposition::Transposition(float eval, unsigned int depth, TranspositionFlag transpositionFlag) {
    this->eval = eval;
    this->depth = depth;
    this->flag = transpositionFlag;
}