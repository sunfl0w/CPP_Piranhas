#pragma once

#include "Piranhas/Move.hpp"
#include "Piranhas/FieldType.hpp"
#include "Piranhas/Direction.hpp"
#include "Piranhas/Position.hpp"

namespace Piranhas {
    struct PerformedMove {
        Move move;
        Position destinationPos;
        FieldType formerDestinationFieldType;

        PerformedMove() {}
        PerformedMove(const Move &move, const Position &destinationPos, FieldType formerDestinationFieldType) {
            this->move = move;
            this->destinationPos = destinationPos;
            this->formerDestinationFieldType = formerDestinationFieldType;
        }
    };
}