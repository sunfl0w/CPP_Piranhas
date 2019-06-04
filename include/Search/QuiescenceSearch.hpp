#pragma once

#include <vector>

#include "GameState.hpp"
#include "Move.hpp"
#include "EvaluatedGameState.hpp"
#include "Evaluator.hpp"
#include "SearchInformation.hpp"

using namespace Search;
using namespace Search::Helpers;

namespace Search {
    class QuiescenceSearch {
    private:
        QuiescenceSearch();
        static std::vector<GameState> GetChildGameStatesWithCaptures(const GameState &gameState);

    public:
        static EvaluatedGameState Search(const GameState &gameState, unsigned int depth, float alpha, float beta, const SearchInformation &searchInformation);
    };
} // namespace Search