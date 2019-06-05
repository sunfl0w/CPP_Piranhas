#include "TranspositionTable.hpp"

using namespace Client::Storage;

TranspositionTable::TranspositionTable() {
    Init();
}

void TranspositionTable::Init() {
    std::random_device randomDevice;
    std::mt19937_64 randomGen(randomDevice());
    std::uniform_int_distribution<unsigned long long> distribution;

    for (int p = 0; p < 2; p++) {
        for (int x = 0; x < 10; x++) {
            for (int y = 0; y < 10; y++) {
                for (int z = 0; z < 4; z++) {
                    zobristTable[p][x][y][z] = distribution(randomGen);
                }
            }
        }
    }
}

unsigned long long TranspositionTable::ComputeKey(const Piranhas::GameState &gameState) const {
    unsigned long long zobristKey = 0;
    int p = 0;
    if(gameState.currentPlayer.color == Piranhas::PlayerColor::Red) {
        p = 0;
    } else if(gameState.currentPlayer.color == Piranhas::PlayerColor::Blue) {
        p = 1;
    }

    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            Piranhas::FieldType fieldType = gameState.board.GetField(x, y).fieldType;
            int z = 0;
            if (fieldType == Piranhas::FieldType::Empty) {
                z = 0;
            } else if (fieldType == Piranhas::FieldType::Red) {
                z = 1;
            } else if (fieldType == Piranhas::FieldType::Blue) {
                z = 2;
            } else {
                z = 3;
            }
            zobristKey ^= zobristTable[p][x][y][z];
        }
    }
    return zobristKey;
}

const Transposition &TranspositionTable::GetTransposition(const Piranhas::GameState &gameState) const {
    auto iterator = table.find(ComputeKey(gameState));

    if (iterator != table.end()) {
        return iterator->second;
    } else {
        return Transposition(0.0f, 0, TranspositionFlag::Exact, Piranhas::Move(Piranhas::Position(0, 0), Piranhas::Direction::Up));
    }
}

bool TranspositionTable::HasTransposition(const Piranhas::GameState &gameState) const {
    auto iterator = table.find(ComputeKey(gameState));

    if (iterator != table.end()) {
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