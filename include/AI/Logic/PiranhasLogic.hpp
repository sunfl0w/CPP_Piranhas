#pragma once

#include <vector>

#include "Piranhas/GameState.hpp"
#include "Piranhas/Move.hpp"
#include "Piranhas/Player.hpp"
#include "Piranhas/PlayerColor.hpp"

namespace AI::Logic {
    class PiranhasLogic {
    protected:
        int searchTimeInMs;

    public:
        PiranhasLogic(int searchTimeInMs);
        virtual Piranhas::Move GetNextMove(Piranhas::GameState currentGameState, Piranhas::PlayerColor ownPlayerColor) = 0;
    };
} // namespace Piranhas::Logic