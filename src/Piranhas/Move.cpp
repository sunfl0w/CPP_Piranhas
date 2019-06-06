#include "Piranhas/Move.hpp"

#include "Piranhas/Direction.hpp"
#include "Piranhas/GameState.hpp"
#include "Piranhas/Position.hpp"

using Piranhas::Move;
using Piranhas::Direction;
using Piranhas::Position;

Move::Move() {}

Move::Move(Position startPos, Direction dir) {
    this->startPos = startPos;
    this->dir = dir;
}

Move::Move(Move &move) {
    this->startPos = move.startPos;
    this->dir = move.dir;
}

Move::Move(const Move &move) {
    this->startPos = move.startPos;
    this->dir = move.dir;
}

Position Move::GetStartPosition() const {
    return startPos;
}

Direction Move::GetDirection() const {
    return dir;
}

Position Move::GetShiftPosition() const {
    int shiftX = 0;
    int shiftY = 0;

    switch (dir) {
    case Direction::Up_Right:
        shiftX = 1;
        shiftY = 1;
        break;
    case Direction::Up:
        shiftY = 1;
        break;
    case Direction::Down_Right:
        shiftX = 1;
        shiftY = -1;
        break;
    case Direction::Right:
        shiftX = 1;
        break;
    case Direction::Down_Left:
        shiftX = -1;
        shiftY = -1;
        break;
    case Direction::Down:
        shiftY = -1;
        break;
    case Direction::Up_Left:
        shiftX = -1;
        shiftY = 1;
        break;
    case Direction::Left:
        shiftX = -1;
        break;
    }
    return Position(shiftX, shiftY);
}