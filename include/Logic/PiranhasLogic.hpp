#pragma once

#include <vector>

#include "GameState.hpp"
#include "Move.hpp"
#include "Player.hpp"
#include "PlayerColor.hpp"

namespace Piranhas::Logic {
    class PiranhasLogic {
    protected:
        int searchTimeInMs;

    public:
        PiranhasLogic(int searchTimeInMs);
        virtual Move GetNextMove(GameState currentGameState, PlayerColor ownPlayerColor) = 0;
    };
} // namespace Piranhas::Logic