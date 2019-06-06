#include "AI/Search/SearchAlgorithms/NegamaxSearch.hpp"

using namespace AI::Search::SearchAlgorithms;
using namespace AI::Search::Helpers;
using namespace AI::MoveOrdering;
using namespace AI::Evaluation;
using namespace Piranhas;

NegamaxSearch::NegamaxSearch() {}

EvaluatedGameState NegamaxSearch::Search(const GameState &gameState, int depth, float alpha, float beta, bool maximizing, const SearchInformation &searchInformation) {
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - searchInformation.searchStartTimePoint).count() > searchInformation.maxSearchTimeInMs) {
        return EvaluatedGameState(gameState, 0.0f);
    }
    if (depth == 0 || gameState.IsGameOver()) {
        float eval = Evaluator::EvaluateGameState(gameState);
        return EvaluatedGameState(gameState, eval);
    }

    std::vector<GameState> childGameStates = MoveOrderer::GetOrderedChildGameStates(gameState, searchInformation.ownPlayerColor);
    EvaluatedGameState maxEval = EvaluatedGameState(childGameStates[0], -10000000.0f);

    for (GameState childGameState : childGameStates) {
        EvaluatedGameState eval = EvaluatedGameState(childGameState, -(Search(childGameState, depth - 1, -beta, -alpha, !maximizing, searchInformation).eval));
        if (eval.eval > maxEval.eval) {
            maxEval = eval;
        }
        alpha = std::max(alpha, maxEval.eval);
        if (alpha >= beta) {
            break;
        }
    }
    return maxEval;
}