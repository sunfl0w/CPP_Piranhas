#pragma once

#include <vector>
#include <iostream>

#include "Move.hpp"
#include "GameState.hpp"

using namespace Piranhas;

namespace Search::Heuristics {
    class KillerHeuristic {
    private:
        Move killerMoves[60][3];

    public:
        KillerHeuristic();
        void AddKillerMove(const Move &move, unsigned int turnCount);
        std::vector<Move> GetValidKillerMoves(const GameState &gameState) const;
    };
} // namespace Search::Heuristics