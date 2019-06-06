#pragma once

#include <algorithm>
#include <vector>

#include "AI/Heuristics/KillerHeuristic.hpp"
#include "AI/Search/Helpers/EvaluatedMove.hpp"
#include "AI/Transposition/TranspositionTable.hpp"
#include "Piranhas/GameState.hpp"
#include "Piranhas/Move.hpp"

namespace AI::MoveOrdering {
    class MoveOrderer {
    private:
        MoveOrderer();
        static float EvaluateMove(const Piranhas::Move &move, const Piranhas::GameState &gameState);

    public:
        static std::vector<Piranhas::Move> GetOrderedPossibleMoves(const Piranhas::GameState &gameState, const Piranhas::PlayerColor maximizingPlayerColor);
        static std::vector<Piranhas::Move> GetOrderedPossibleMoves(const Piranhas::GameState &gameState, const Piranhas::PlayerColor maximizingPlayerColor, const AI::Heuristics::KillerHeuristic *killerHeuristic, const AI::Transposition::TranspositionTable *transpositionTable);
        static std::vector<Piranhas::GameState> GetOrderedChildGameStates(const Piranhas::GameState &gameState, const Piranhas::PlayerColor maximizingPlayerColor);
        static std::vector<Piranhas::GameState> GetOrderedChildGameStates(const Piranhas::GameState &gameState, const Piranhas::PlayerColor maximizingPlayerColor, const AI::Heuristics::KillerHeuristic *killerHeuristic, const AI::Transposition::TranspositionTable *transpositionTable);
    };
} // namespace Search::MoveOrdering