#pragma once

#include <vector>
#include <algorithm>

#include "Move.hpp"
#include "GameState.hpp"
#include "EvaluatedMove.hpp"
#include "KillerHeuristic.hpp"
#include "TranspositionTable.hpp"

using namespace Piranhas;
using namespace Search::Heuristics;
using namespace Client::Storage;

namespace Search {
    class MoveOrdering {
    private:
        MoveOrdering();
        static float EvaluateMove(const Move &move, const GameState &gameState);
    public:
        static std::vector<Move> GetOrderedPossibleMoves(const GameState &gameState, const PlayerColor maximizingPlayerColor);
        static std::vector<Move> GetOrderedPossibleMoves(const GameState &gameState, const PlayerColor maximizingPlayerColor, const KillerHeuristic *killerHeuristic, const TranspositionTable *transpositionTable);
        static std::vector<GameState> GetOrderedChildGameStates(const GameState &gameState, const PlayerColor maximizingPlayerColor);
        static std::vector<GameState> GetOrderedChildGameStates(const GameState &gameState, const PlayerColor maximizingPlayerColor, const KillerHeuristic *killerHeuristic, const TranspositionTable *transpositionTable);
    };
} // namespace Search