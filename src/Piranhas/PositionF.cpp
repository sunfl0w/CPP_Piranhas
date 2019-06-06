#include "Piranhas/PositionF.hpp"

using Piranhas::PositionF;

PositionF::PositionF() {
    this->x = 0;
    this->y = 0;
}

PositionF::PositionF(float x, float y) {
    this->x = x;
    this->y = y;
}

bool PositionF::operator==(const PositionF &position) const {
    if(x == position.x && y == position.y) {
        return true;
    } else {
        return false;
    }
}