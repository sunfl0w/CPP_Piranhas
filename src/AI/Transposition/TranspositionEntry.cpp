#include "AI/Transposition/TranspositionEntry.hpp"

using namespace AI::Transposition;

TranspositionEntry::TranspositionEntry(float eval, unsigned int depth, TranspositionFlag transpositionFlag, Piranhas::Move hashMove) {
    this->eval = eval;
    this->depth = depth;
    this->flag = transpositionFlag;
    this->hashMove = hashMove;
}