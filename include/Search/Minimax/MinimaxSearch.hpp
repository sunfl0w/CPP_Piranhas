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
#include "EvaluatorForMinimax.hpp"
#include "SearchInformation.hpp"
#include "KillerHeuristic.hpp"
#include "MoveOrdering.hpp"

using namespace Piranhas;
using namespace Search::Helpers;
using namespace Search;
using namespace Search::Heuristics;

namespace Search {
    class MinimaxSearch {
        //KillerHeuristic* killerHeuristic;

    public:
        MinimaxSearch();
        EvaluatedGameState Search(const GameState &gameState, int depth, bool maximizing, const SearchInformation &searchInformation);
    };
} // namespace Search::Negamax