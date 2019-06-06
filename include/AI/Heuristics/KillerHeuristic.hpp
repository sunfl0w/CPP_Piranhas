#pragma once

#include <vector>
#include <iostream>

#include "Piranhas/Move.hpp"
#include "Piranhas/GameState.hpp"

namespace AI::Heuristics {
    class KillerHeuristic {
    private:
        Piranhas::Move killerMoves[60][3];

    public:
        KillerHeuristic();
        void AddKillerMove(const Piranhas::Move &move, unsigned int turnCount);
        std::vector<Piranhas::Move> GetValidKillerMoves(const Piranhas::GameState &gameState) const;
    };
} // namespace Search::Heuristics