#pragma once

#include <chrono>
#include <random>
#include <time.h>
#include <math.h>
#include <algorithm>

#include "Piranhas/GameResult.hpp"
#include "Piranhas/GameState.hpp"
#include "Piranhas/Move.hpp"
#include "AI/Search/Helpers/EvaluatedGameState.hpp"
#include "AI/Search/Helpers/EvaluatedMove.hpp"
#include "AI/Evaluation/Evaluator.hpp"
#include "AI/Search/Helpers/SearchInformation.hpp"
#include "AI/MoveOrdering/MoveOrderer.hpp"

namespace AI::Search::SearchAlgorithms {
    class NegamaxSearch {
        NegamaxSearch();

    public:
        static AI::Search::Helpers::EvaluatedGameState Search(const Piranhas::GameState &gameState, int depth, float alpha, float beta, bool maximizing, const AI::Search::Helpers::SearchInformation &searchInformation);
    };
} // namespace Search::Negamax