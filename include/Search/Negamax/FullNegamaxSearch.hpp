#pragma once

#include <chrono>
#include <random>
#include <time.h>
#include <math.h>
#include <algorithm>

#include "NullMoveHeuristic.hpp"
#include "GameResult.hpp"
#include "GameState.hpp"
#include "Move.hpp"
#include "EvaluatedGameState.hpp"
#include "EvaluatedMove.hpp"
#include "Evaluator.hpp"
#include "SearchInformation.hpp"
#include "KillerHeuristic.hpp"
#include "MoveOrdering.hpp"
#include "QuiescenceSearch.hpp"
#include "TranspositionTable.hpp"

using namespace Piranhas;
using namespace Search::Helpers;
using namespace Search;
using namespace Search::Heuristics;
using namespace Client::Storage;

namespace Search {
    class FullNegamaxSearch {
        KillerHeuristic* killerHeuristic;
        TranspositionTable* transpositionTable;

    public:
        FullNegamaxSearch(KillerHeuristic *killerHeuristic, TranspositionTable* transpositionTable);
        EvaluatedGameState Search(const GameState &gameState, int depth, float alpha, float beta, const SearchInformation &searchInformation, bool allownNullMove);
    };
} // namespace Search::Negamax