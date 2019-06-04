#include "TranspositionTable.hpp"

using namespace Client::Storage;

TranspositionTable::TranspositionTable() {
    Init();
}

void TranspositionTable::Init() {
    std::random_device randomDevice;
    std::mt19937_64 randomGen(randomDevice());
    std::uniform_int_distribution<unsigned long long> distribution;

    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            for (int z = 0; z < 3; z++) {
                zobristTable[x][y][z] = distribution(randomGen);
            }
        }
    }
}

unsigned long long TranspositionTable::ComputeKey(const Piranhas::Board &board) const {
    unsigned long long zobristKey = 0;
    for(int x = 0; x < 10; x++) {
        for(int y = 0; y < 10; y++) {
            Piranhas::FieldType fieldType = board.GetField(x, y).fieldType;
            if(fieldType != Piranhas::FieldType::Empty) {
                int z = 0;
                if(fieldType == Piranhas::FieldType::Red) {
                    z = 1;
                } else if(fieldType == Piranhas::FieldType::Blue) {
                    z = 2;
                }
                zobristKey ^= zobristTable[x][y][z];
            }
        }
    }
    return zobristKey;
}

const Transposition &TranspositionTable::GetTransposition(const Piranhas::GameState &gameState) const {
    auto iterator = table.find(ComputeKey(gameState.board));

    if(iterator != table.end()) {
        return iterator->second;
    } else {
        return Transposition(0.0f, 0, TranspositionFlag::Exact);
    }
}

bool TranspositionTable::HasTransposition(const Piranhas::GameState &gameState) const {
     auto iterator = table.find(ComputeKey(gameState.board));

    if(iterator != table.end()) {
        return true;
    } else {
        return false;
    }
}

void TranspositionTable::AddTransposition(unsigned long long zobristKey, const Transposition &transposition) {
    table.insert(std::make_pair(zobristKey, transposition));
}

int TranspositionTable::GetSize() const {
    return table.size();
}