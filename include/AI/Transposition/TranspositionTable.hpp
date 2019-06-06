#pragma once

#include <unordered_map>
#include <random>

#include "Piranhas/Board.hpp"
#include "Piranhas/GameState.hpp"
#include "Piranhas/FieldType.hpp"
#include "Piranhas/Direction.hpp"
#include "Piranhas/Position.hpp"
#include "Piranhas/PlayerColor.hpp"

#include "AI/Transposition/TranspositionEntry.hpp"

namespace AI::Transposition {
    class TranspositionTable {
    private:
        unsigned long long zobristTable[2][10][10][4];
        std::unordered_map<unsigned long long, TranspositionEntry> table;

        void Init();

    public:
        TranspositionTable();

        unsigned long long ComputeKey(const Piranhas::GameState &gameState) const;
        const TranspositionEntry &GetTranspositionEntry(const Piranhas::GameState &gameState) const;
        bool HasTranspositionEntry(const Piranhas::GameState &gameState) const;
        void AddTranspositionEntry(unsigned long long zobristKey, const TranspositionEntry &transpositionEntry);
        int GetSize() const;
    };
} // namespace Client::Storage