#pragma once

#include <vector>

#include "AI/Evaluation/Evaluator.hpp"
#include "AI/Search/Helpers/EvaluatedGameState.hpp"
#include "AI/Search/Helpers/SearchInformation.hpp"
#include "Piranhas/GameState.hpp"
#include "Piranhas/Move.hpp"

namespace AI::Search::SearchAlgorithms {
    class QuiescenceSearch {
    private:
        std::vector<Piranhas::Move> GetMovesWithCaptures(const Piranhas::GameState &gameState);

    public:
        int nodesSearched;

        QuiescenceSearch();
        AI::Search::Helpers::EvaluatedGameState Search(Piranhas::GameState &gameState, unsigned int depth, float alpha, float beta, const AI::Search::Helpers::SearchInformation &searchInformation);
    };
} // namespace AI::Search::SearchAlgorithms