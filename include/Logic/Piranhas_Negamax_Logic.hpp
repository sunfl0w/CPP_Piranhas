#pragma once

#include "Negamax_Search.hpp"
#include "PiranhasLogic.hpp"
#include "MoveSearch.hpp"

using namespace Piranhas::Logic;

namespace Piranhas::Logic {
    class Piranhas_Negamax_Logic : public PiranhasLogic {
    private:
        Piranhas_Negamax_Logic();

    public:
        Piranhas_Negamax_Logic(int searchTimeInMs);
        Move GetNextMove(GameState currentGameState, PlayerColor ownPlayerColor);
    };
} // namespace Piranhas::Logic