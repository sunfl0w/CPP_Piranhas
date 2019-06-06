#pragma once

#include "AI/Search/SearchAlgorithms/MCTS/MCTS_Search.hpp"
#include "AI/Logic/PiranhasLogic.hpp"

namespace AI::Logic {
    class Piranhas_MCTS_Logic : public PiranhasLogic {
    private:
        Piranhas_MCTS_Logic();

    public:
        Piranhas_MCTS_Logic(int searchTimeInMs);
        Piranhas::Move GetNextMove(Piranhas::GameState currentGameState);
    };
} // namespace Piranhas::Logic