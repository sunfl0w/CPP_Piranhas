#include "MinimaxSearch.hpp"

using namespace Search::Evaluation;
using namespace Search;
using namespace Search::Heuristics;

MinimaxSearch::MinimaxSearch() {}

EvaluatedGameState MinimaxSearch::Search(const GameState &gameState, int depth, bool maximizing, const SearchInformation &searchInformation) {
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - searchInformation.searchStartTimePoint).count() > searchInformation.maxSearchTimeInMs) {
        return EvaluatedGameState(gameState, 0.0f);
    }
    if (depth == 0 || gameState.IsGameOver()) {
        float eval = EvaluatorForMinimax::EvaluateGameState(gameState, searchInformation.ownPlayerColor);
        return EvaluatedGameState(gameState, eval);
    }

    if(maximizing) {
        std::vector<GameState> childGameStates = MoveOrdering::GetOrderedChildGameStates(gameState, searchInformation.ownPlayerColor);
        EvaluatedGameState maxEval = EvaluatedGameState(childGameStates[0], -10000.0f);
        for (GameState childGameState : childGameStates) {
            EvaluatedGameState eval = EvaluatedGameState(childGameState, Search(childGameState, depth - 1, false, searchInformation).eval);
            if(eval.eval > maxEval.eval) {
                maxEval = EvaluatedGameState(eval);
            }
        }
        return maxEval;
    } else {
        std::vector<GameState> childGameStates = MoveOrdering::GetOrderedChildGameStates(gameState, searchInformation.ownPlayerColor);
        EvaluatedGameState minEval = EvaluatedGameState(childGameStates[0], 10000.0f);
        for (GameState childGameState : childGameStates) {
            EvaluatedGameState eval = EvaluatedGameState(childGameState, Search(childGameState, depth - 1, true, searchInformation).eval);
            if(eval.eval < minEval.eval) {
                minEval = EvaluatedGameState(eval);
            }
        }
        return minEval;
    }
}