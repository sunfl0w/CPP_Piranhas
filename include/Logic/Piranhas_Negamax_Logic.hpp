#pragma once

#include "Negamax_Search.hpp"
#include "PiranhasLogic.hpp"

using namespace Piranhas::Logic;

namespace Piranhas::Logic {
    class Piranhas_Negamax_Logic : public PiranhasLogic {
    private:
        Piranhas_Negamax_Logic();

    public:
        Piranhas_Negamax_Logic(int searchTimeInMs);
        Move GetNextMove(GameState currentGameState);
    };
} // namespace Piranhas::Logic