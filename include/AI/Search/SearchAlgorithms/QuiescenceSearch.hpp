#pragma once

#include <vector>

#include "Piranhas/GameState.hpp"
#include "Piranhas/Move.hpp"
#include "AI/Search/Helpers/EvaluatedGameState.hpp"
#include "AI/Evaluation/Evaluator.hpp"
#include "AI/Search/Helpers/SearchInformation.hpp"

namespace AI::Search::SearchAlgorithms {
    class QuiescenceSearch {
    private:
        QuiescenceSearch();
        static std::vector<Piranhas::GameState> GetChildGameStatesWithCaptures(const Piranhas::GameState &gameState);

    public:
        static AI::Search::Helpers::EvaluatedGameState Search(const Piranhas::GameState &gameState, unsigned int depth, float alpha, float beta, const AI::Search::Helpers::SearchInformation &searchInformation);
    };
} // namespace Search