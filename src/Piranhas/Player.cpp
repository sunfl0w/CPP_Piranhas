#include "Piranhas/Player.hpp"

#include "Piranhas/PlayerColor.hpp"
#include "Piranhas/FieldType.hpp"

using Piranhas::Player;
using Piranhas::FieldType;
using Piranhas::PlayerColor;

Player::Player() {}

Player::Player(PlayerColor playerColor) {
    this->color = playerColor;
    this->fieldType = PlayerColorToFieldType(playerColor);
}

FieldType Player::PlayerColorToFieldType(PlayerColor playerColor) const {
    if(playerColor == PlayerColor::Red) {
        return FieldType::Red;
    } else {
        return FieldType::Blue;
    }
}

Player Player::GetOppositePlayer() const {
    if(color == PlayerColor::Red) {
        return Player(PlayerColor::Blue);
    } else {
        return Player(PlayerColor::Red);
    }
}