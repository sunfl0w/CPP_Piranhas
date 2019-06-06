#pragma once

#include "AI/Logic/PiranhasLogic.hpp"
#include "AI/Search/MoveSearch.hpp"

namespace AI::Logic {
    class Piranhas_Negamax_Logic : public PiranhasLogic {
    private:
        Piranhas_Negamax_Logic();
        AI::Search::MoveSearch moveSearch;
    public:
        Piranhas_Negamax_Logic(int searchTimeInMs);
        Piranhas::Move GetNextMove(Piranhas::GameState currentGameState, Piranhas::PlayerColor ownPlayerColor);
    };
} // namespace Piranhas::Logic