#pragma once

#include "Piranhas/PlayerColor.hpp"
#include "Piranhas/FieldType.hpp"


namespace Piranhas {
    class Player {
        public: 
        PlayerColor color;
        FieldType fieldType;

        Player();
        Player(PlayerColor color);

        FieldType PlayerColorToFieldType(PlayerColor playerColor) const;
        Player GetOppositePlayer() const;
    };
} // namespace Pirnhas