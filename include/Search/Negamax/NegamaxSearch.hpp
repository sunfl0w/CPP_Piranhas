#pragma once

#include <chrono>
#include <random>
#include <time.h>
#include <math.h>
#include <algorithm>

#include "GameResult.hpp"
#include "GameState.hpp"
#include "Move.hpp"
#include "EvaluatedGameState.hpp"
#include "EvaluatedMove.hpp"
#include "Evaluator.hpp"
#include "SearchInformation.hpp"
#include "MoveOrdering.hpp"

using namespace Piranhas;
using namespace Search::Helpers;
using namespace Search;

namespace Search {
    class NegamaxSearch {
        NegamaxSearch();

    public:
        static EvaluatedGameState Search(const GameState &gameState, int depth, float alpha, float beta, bool maximizing, const SearchInformation &searchInformation);
    };
} // namespace Search::Negamax