#include "AI/Heuristics/KillerHeuristic.hpp"

using namespace AI::Heuristics;
using namespace Piranhas;

KillerHeuristic::KillerHeuristic() {}

void KillerHeuristic::AddKillerMove(const Move &move, unsigned int turnCount) {
    killerMoves[turnCount][0] = Move(killerMoves[turnCount][1]);
    killerMoves[turnCount][1] = Move(killerMoves[turnCount][2]);
    killerMoves[turnCount][2] = Move(move);
}

std::vector<Move> KillerHeuristic::GetValidKillerMoves(const GameState &gameState) const {
    std::vector<Move> validKillerMoves;
    for(int i = 0; i < 3; i++) {
        Move killerMove = killerMoves[gameState.turnCount][i];
        if(gameState.IsMoveValid(killerMove)) {
            validKillerMoves.push_back(killerMove);
        }
    }
    return validKillerMoves;
}