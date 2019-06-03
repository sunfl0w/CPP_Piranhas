#pragma once

#include "PiranhasLogic.hpp"
#include "MoveSearch.hpp"

using namespace Piranhas::Logic;

namespace Piranhas::Logic {
    class Piranhas_Negamax_Logic : public PiranhasLogic {
    private:
        Piranhas_Negamax_Logic();
        MoveSearch moveSearch;
    public:
        Piranhas_Negamax_Logic(int searchTimeInMs);
        Move GetNextMove(GameState currentGameState, PlayerColor ownPlayerColor);
    };
} // namespace Piranhas::Logic