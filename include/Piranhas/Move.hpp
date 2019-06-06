#pragma once

#include "Piranhas/Position.hpp"
#include "Piranhas/Direction.hpp"
#include "Piranhas/FieldType.hpp"

namespace Piranhas {
    class Move {
        Position startPos;
        Direction dir;

    public:
        Move();
        Move(Position startPos, Direction dir);
        Move(Move &move);
        Move(const Move &move);

        Position GetStartPosition() const;
        Direction GetDirection() const;

        Position GetShiftPosition() const;
    };
} // namespace Piranhas