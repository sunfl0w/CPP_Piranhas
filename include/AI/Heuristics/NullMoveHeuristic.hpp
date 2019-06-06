#pragma once

#include "Piranhas/GameState.hpp"
#include "AI/Search/SearchAlgorithms/NegamaxSearch.hpp"
#include "AI/Search/Helpers/SearchInformation.hpp"
#include "AI/Search/Helpers/EvaluatedGameState.hpp"

namespace AI::Heuristics {
    class NullMoveHeuristic {
    private:
        NullMoveHeuristic();
    public:
        static AI::Search::Helpers::EvaluatedGameState Search(const Piranhas::GameState &gameState, unsigned int depth, float alpha, float beta, bool maximizing, unsigned int depthReduction, const AI::Search::Helpers::SearchInformation &searchInformation);
    };
} // namespace Search
