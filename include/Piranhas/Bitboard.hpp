#pragma once

#include <bitset>
#include <memory>
#include <array>

#include "Field.hpp"
#include "FieldType.hpp"
#include "Position.hpp"

namespace Piranhas {
    class Bitboard {
    public:
        //std::bitset<100> redFields;
        //std::bitset<100> blueFields;
        //std::bitset<100> obstacleFields;
        //std::bitset<100> emptyFields;

        //std::array<char, 100> redFields;
        //std::array<char, 100> blueFields;
        //std::array<char, 100> obstacleFields;
        //std::array<char, 100> emptyFields;

        std::array<Field, 100> fields;

    private:
        FieldType GetFieldTypeAtPosition(const Position &pos) const;

        void SetFieldTypeAtPosition(const Position &pos, FieldType fieldType);

    public:
        Bitboard();
        Bitboard(Bitboard &bitboard);
        Bitboard(const Bitboard &bitboard);

        Field GetField(const Position &pos) const;

        void SetField(const Position &pos, FieldType fieldType);
    };
} // namespace Piranhas