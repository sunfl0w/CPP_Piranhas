#pragma once

#include "MCTS_Search.hpp"
#include "PiranhasLogic.hpp"

using namespace Piranhas::Logic;

namespace Piranhas::Logic {
    class Piranhas_MCTS_Logic : public PiranhasLogic {
    private:
        Piranhas_MCTS_Logic();

    public:
        Piranhas_MCTS_Logic(int searchTimeInMs);
        Move GetNextMove(GameState currentGameState);
    };
} // namespace Piranhas::Logic