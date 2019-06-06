#include "Bitboard.hpp"

using namespace Piranhas;

FieldType Bitboard::GetFieldTypeAtPosition(const Position &pos) const {
    int index = pos.y * 10 + pos.x;
    /*if(emptyFields[index] == 1) {
        return FieldType::Empty;
    } else if (redFields[index] == 1) {
        return FieldType::Red;
    } else if (blueFields[index] == 1) {
        return FieldType::Blue;
    } else {
        return FieldType::Obstacle;
    }*/
    return fields[index].fieldType;
}

void Bitboard::SetFieldTypeAtPosition(const Position &pos, FieldType fieldType) {
    int index = pos.y * 10 + pos.x;
    /*if (fieldType == FieldType::Empty) {
        redFields[index] = 0;
        blueFields[index] = 0;
        obstacleFields[index] = 0;
        emptyFields[index] = 1;
    } else if (fieldType == FieldType::Red) {
        redFields[index] = 1;
        blueFields[index] = 0;
        obstacleFields[index] = 0;
        emptyFields[index] = 0;
    } else if (fieldType == FieldType::Blue) {
        redFields[index] = 0;
        blueFields[index] = 1;
        obstacleFields[index] = 0;
        emptyFields[index] = 0;
    } else {
        redFields[index] = 0;
        blueFields[index] = 0;
        obstacleFields[index] = 1;
        emptyFields[index] = 0;
    }*/
    fields[index].fieldType = fieldType;
}

Bitboard::Bitboard() {
    //redFields = std::bitset<100>(0);
    //blueFields = std::bitset<100>(0);
    //obstacleFields = std::bitset<100>(0);
    //emptyFields = std::bitset<100>(0);
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            fields[y * 10 + x].fieldType = FieldType::Empty;
            fields[y * 10 + x].position = Position(x, y);
        }
    }
}

Bitboard::Bitboard(Bitboard &bitboard) {
    /*this->redFields = std::bitset<100>(bitboard.redFields);
    this->blueFields = std::bitset<100>(bitboard.blueFields);
    this->obstacleFields = std::bitset<100>(bitboard.obstacleFields);
    this->emptyFields = std::bitset<100>(bitboard.emptyFields);*/

    /*this->redFields = std::array<char, 100>(bitboard.redFields);
    this->blueFields = std::array<char, 100>(bitboard.blueFields);
    this->obstacleFields = std::array<char, 100>(bitboard.obstacleFields);
    this->emptyFields = std::array<char, 100>(bitboard.emptyFields);*/

    this->fields = bitboard.fields;
}
Bitboard::Bitboard(const Bitboard &bitboard) {
    /*this->redFields = std::bitset<100>(bitboard.redFields);
    this->blueFields = std::bitset<100>(bitboard.blueFields);
    this->obstacleFields = std::bitset<100>(bitboard.obstacleFields);
    this->emptyFields = std::bitset<100>(bitboard.emptyFields);*/

    /*this->redFields = std::array<char, 100>(bitboard.redFields);
    this->blueFields = std::array<char, 100>(bitboard.blueFields);
    this->obstacleFields = std::array<char, 100>(bitboard.obstacleFields);
    this->emptyFields = std::array<char, 100>(bitboard.emptyFields);*/

    this->fields = bitboard.fields;
}

Field Bitboard::GetField(const Position &pos) const {
    //FieldType fieldType = GetFieldTypeAtPosition(pos);
    //Position position = Position(pos);
    //Field field = Field(GetFieldTypeAtPosition(pos), Position(pos));
    return fields[pos.y * 10 + pos.x];
    //return Field(GetFieldTypeAtPosition(pos), Position(pos));
}

void Bitboard::SetField(const Position &pos, FieldType fieldType) {
    SetFieldTypeAtPosition(pos, fieldType);
}