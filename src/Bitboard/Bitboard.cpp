#include "Bitboard.hpp"

using namespace Piranhas;

FieldType Bitboard::GetFieldTypeAtPosition(const Position &pos) const {
    int index = pos.y * 10 + pos.x;
    if (redFields[index] == 1) {
        return FieldType::Red;
    } else if (blueFields[index] == 1) {
        return FieldType::Blue;
    } else if (obstacleFields[index] == 1) {
        return FieldType::Obstacle;
    } else {
        return FieldType::Empty;
    }
}

void Bitboard::SetFieldTypeAtPosition(const Position &pos, FieldType fieldType) {
    int index = pos.y * 10 + pos.x;
    if (fieldType == FieldType::Red) {
        redFields[index] = 1;
        blueFields[index] = 0;
        obstacleFields[index] = 0;
        emptyFields[index] = 0;
    } else if (fieldType == FieldType::Blue) {
        redFields[index] = 0;
        blueFields[index] = 1;
        obstacleFields[index] = 0;
        emptyFields[index] = 0;
    } else if (fieldType == FieldType::Obstacle) {
        redFields[index] = 0;
        blueFields[index] = 0;
        obstacleFields[index] = 1;
        emptyFields[index] = 0;
    } else {
        redFields[index] = 0;
        blueFields[index] = 0;
        obstacleFields[index] = 0;
        emptyFields[index] = 1;
    }
}

Bitboard::Bitboard() {
    //redFields = std::bitset<100>(0);
    //blueFields = std::bitset<100>(0);
    //obstacleFields = std::bitset<100>(0);
    //emptyFields = std::bitset<100>(0);
}

Bitboard::Bitboard(Bitboard &bitboard) {
    this->redFields = std::bitset<100>(bitboard.redFields);
    this->blueFields = std::bitset<100>(bitboard.blueFields);
    this->obstacleFields = std::bitset<100>(bitboard.obstacleFields);
    this->emptyFields = std::bitset<100>(bitboard.emptyFields);
}
Bitboard::Bitboard(const Bitboard &bitboard) {
    this->redFields = std::bitset<100>(bitboard.redFields);
    this->blueFields = std::bitset<100>(bitboard.blueFields);
    this->obstacleFields = std::bitset<100>(bitboard.obstacleFields);
    this->emptyFields = std::bitset<100>(bitboard.emptyFields);
}

Field Bitboard::GetField(const Position &pos) const {
    //FieldType fieldType = GetFieldTypeAtPosition(pos);
    //Position position = Position(pos);
    //Field field = Field(GetFieldTypeAtPosition(pos), Position(pos));
    return Field(GetFieldTypeAtPosition(pos), Position(pos));
}

void Bitboard::SetField(const Position &pos, FieldType fieldType) {
    SetFieldTypeAtPosition(pos, fieldType);
}