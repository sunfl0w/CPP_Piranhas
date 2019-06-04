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

using namespace Piranhas;
using namespace Search::Helpers;
using namespace Search;
using namespace Search::Heuristics;

namespace Search {
    class FullNegamaxSearch {
        KillerHeuristic* killerHeuristic;

    public:
        FullNegamaxSearch(KillerHeuristic *killerHeuristic);
        EvaluatedGameState Search(const GameState &gameState, int depth, float alpha, float beta, const SearchInformation &searchInformation, bool allownNullMove);
    };
} // namespace Search::Negamax