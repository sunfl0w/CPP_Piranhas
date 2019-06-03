#pragma once

#include "GameState.hpp"
#include "NegamaxSearch.hpp"
#include "SearchInformation.hpp"
#include "EvaluatedGameState.hpp"

using namespace Piranhas;
using namespace Search;
using namespace Search::Helpers;

namespace Search::Heuristics {
    class NullMoveHeuristic {
    private:
        NullMoveHeuristic();
    public:
        static EvaluatedGameState Search(const GameState &gameState, unsigned int depth, float alpha, float beta, bool maximizing, unsigned int depthReduction, const SearchInformation &searchInformation);
    };
} // namespace Search
