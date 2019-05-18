#include "Bitboard.hpp"

using namespace Piranhas;

FieldType Bitboard::GetFieldTypeAtPosition(const Position &pos) {
    if (redFields[pos.y * 10 + pos.x] == 1) {
        return FieldType::Red;
    } else if (blueFields[pos.y * 10 + pos.x] == 1) {
        return FieldType::Blue;
    } else if (obstacleFields[pos.y * 10 + pos.x] == 1) {
        return FieldType::Obstacle;
    } else {
        return FieldType::Empty;
    }
}

FieldType Bitboard::SetFieldTypeAtPosition(const Position &pos, FieldType fieldType) {

    if (fieldType == FieldType::Red) {
        redFields[pos.y * 10 + pos.x] = 1;
        blueFields[pos.y * 10 + pos.x] = 0;
        obstacleFields[pos.y * 10 + pos.x] = 0;
        emptyFields[pos.y * 10 + pos.x] = 0;
    } else if (fieldType == FieldType::Blue) {
        redFields[pos.y * 10 + pos.x] = 0;
        blueFields[pos.y * 10 + pos.x] = 1;
        obstacleFields[pos.y * 10 + pos.x] = 0;
        emptyFields[pos.y * 10 + pos.x] = 0;
    } else if (fieldType == FieldType::Obstacle) {
        redFields[pos.y * 10 + pos.x] = 0;
        blueFields[pos.y * 10 + pos.x] = 0;
        obstacleFields[pos.y * 10 + pos.x] = 1;
        emptyFields[pos.y * 10 + pos.x] = 0;
    } else {
        redFields[pos.y * 10 + pos.x] = 0;
        blueFields[pos.y * 10 + pos.x] = 0;
        obstacleFields[pos.y * 10 + pos.x] = 0;
        emptyFields[pos.y * 10 + pos.x] = 1;
    }
}

Bitboard::Bitboard() {
    redFields = std::bitset<100>();
    blueFields = std::bitset<100>();
    obstacleFields = std::bitset<100>();
    emptyFields = std::bitset<100>();
}

Bitboard::Bitboard(Bitboard &bitboard) {
    this->redFields = std::bitset<100>(bitboard.redFields);
    this->blueFields = std::bitset<100>(bitboard.blueFields);
    this->obstacleFields = std::bitset<100>(bitboard.obstacleFields);
    this->emptyFields = std::bitset<100>(bitboard.emptyFields);
}

Field &Bitboard::GetField(const Position &pos) {
    Field field = Field(GetFieldTypeAtPosition(pos), Position(pos));
    return field;
}

void Bitboard::SetField(const Position &pos, FieldType fieldType) {
    SetFieldTypeAtPosition(pos, fieldType);
}