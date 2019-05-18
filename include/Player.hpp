#pragma once

#include "PlayerColor.hpp"
#include "FieldType.hpp"


namespace Piranhas {
    class Player {
        public: 
        PlayerColor color;
        FieldType fieldType;

        Player();
        Player(PlayerColor color);

        FieldType PlayerColorToFieldType(PlayerColor playerColor);
        Player GetOppositePlayer();
    };
} // namespace Pirnhas