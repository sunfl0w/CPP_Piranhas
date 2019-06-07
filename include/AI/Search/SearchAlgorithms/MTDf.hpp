#pragma once

#include "AI/Search/Helpers/EvaluatedGameState.hpp"
#include "AI/Search/Helpers/SearchInformation.hpp"
#include "AI/Heuristics/KillerHeuristic.hpp"
#include "AI/Transposition/TranspositionTable.hpp"
#include "AI/Search/SearchAlgorithms/FullNegamaxSearch.hpp"

namespace AI::Search::SearchAlgorithms {
    class MTDfSearch {
        AI::Heuristics::KillerHeuristic* killerHeuristic;
        AI::Transposition::TranspositionTable* transpositionTable;
    public:
        unsigned int nodesSearched = 0;

    public:
        MTDfSearch(AI::Heuristics::KillerHeuristic *killerHeuristic, AI::Transposition::TranspositionTable* transpositionTable);
        AI::Search::Helpers::EvaluatedGameState Search(Piranhas::GameState &gameState, int depth, float guess, const AI::Search::Helpers::SearchInformation &searchInformation);
    };
}