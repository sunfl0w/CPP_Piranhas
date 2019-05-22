#include "Position.hpp"

using Piranhas::Position;

Position::Position() {
    this->x = 0;
    this->y = 0;
}

Position::Position(int x, int y) {
    this->x = x;
    this->y = y;
}

bool Position::operator==(const Position &position) const {
    if(x == position.x && y == position.y) {
        return true;
    } else {
        return false;
    }
}