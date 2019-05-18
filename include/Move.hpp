#pragma once

#include "Position.hpp"
#include "Direction.hpp"
#include "FieldType.hpp"

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