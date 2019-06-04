#pragma once

#include <unordered_map>
#include <random>

#include "Board.hpp"
#include "GameState.hpp"
#include "Transposition.hpp"
#include "FieldType.hpp"

namespace Client::Storage {
    class TranspositionTable {
    private:
        unsigned long long zobristTable[10][10][3];
        std::unordered_map<unsigned long long, Transposition> table;

        void Init();

    public:
        TranspositionTable();

        unsigned long long ComputeKey(const Piranhas::Board &board) const;
        const Transposition &GetTransposition(const Piranhas::GameState &gameState) const;
        bool HasTransposition(const Piranhas::GameState &gameState) const;
        void AddTransposition(unsigned long long zobristKey, const Transposition &transposition);
        int GetSize() const;
    };
} // namespace Client::Storage