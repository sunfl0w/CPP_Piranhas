#pragma once

#include <chrono>
#include <random>
#include <time.h>
#include <math.h>
#include <algorithm>

#include "AI/Heuristics/NullMoveHeuristic.hpp"
#include "Piranhas/GameResult.hpp"
#include "Piranhas/GameState.hpp"
#include "Piranhas/Move.hpp"
#include "AI/Search/Helpers/EvaluatedGameState.hpp"
#include "AI/Search/Helpers/EvaluatedMove.hpp"
#include "AI/Evaluation/Evaluator.hpp"
#include "AI/Search/Helpers/SearchInformation.hpp"
#include "AI/Heuristics/KillerHeuristic.hpp"
#include "AI/MoveOrdering/MoveOrderer.hpp"
#include "AI/Search/SearchAlgorithms/QuiescenceSearch.hpp"
#include "AI/Transposition/TranspositionTable.hpp"

namespace AI::Search::SearchAlgorithms {
    class FullNegamaxSearch {
        AI::Heuristics::KillerHeuristic* killerHeuristic;
        AI::Transposition::TranspositionTable* transpositionTable;
    public:
        unsigned int nodesSearched = 0;

    public:
        FullNegamaxSearch(AI::Heuristics::KillerHeuristic *killerHeuristic, AI::Transposition::TranspositionTable* transpositionTable);
        AI::Search::Helpers::EvaluatedGameState Search(Piranhas::GameState &gameState, int depth, float alpha, float beta, const AI::Search::Helpers::SearchInformation &searchInformation, bool allownNullMove);
    };
} // namespace Search::Negamax