#include "FullNegamaxSearch.hpp"

using namespace Search::Evaluation;
using namespace Search;
using namespace Search::Heuristics;

FullNegamaxSearch::FullNegamaxSearch(KillerHeuristic *killerHeuristic) {
    this->killerHeuristic = killerHeuristic;
}

EvaluatedGameState FullNegamaxSearch::Search(const GameState &gameState, int depth, float alpha, float beta, const SearchInformation &searchInformation, bool allowNullMove) {
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - searchInformation.searchStartTimePoint).count() > searchInformation.maxSearchTimeInMs) {
        return EvaluatedGameState(gameState, 0.0f);
    }
    if (depth == 0 || gameState.IsGameOver()) {
        float eval = Evaluator::EvaluateGameState(gameState);
        //float eval = QuiescenceSearch::Search(gameState, 10, alpha, beta, searchInformation).eval;
        return EvaluatedGameState(gameState, eval);
    }

    if(allowNullMove && depth > 2) {
        int r = 1;
        if(depth > 4) {
            r = 2;
        }

        GameState nullGameState = GameState(gameState);
        nullGameState.SwapPlayers();

        EvaluatedGameState nullEval = EvaluatedGameState(gameState, - Search(nullGameState, depth - r - 1, -beta, -beta + 1, searchInformation, false).eval);
        if(nullEval.eval >= beta) {
            return nullEval;
        }
    }

    std::vector<GameState> childGameStates = MoveOrdering::GetOrderedChildGameStates(gameState, searchInformation.ownPlayerColor, killerHeuristic);
    EvaluatedGameState maxEval = EvaluatedGameState(childGameStates[0], -10000.0f);

    for (GameState childGameState : childGameStates) {
        EvaluatedGameState eval = EvaluatedGameState(childGameState, -(FullNegamaxSearch::Search(childGameState, depth - 1, -beta, -alpha, searchInformation, true).eval));
        if (eval.eval > maxEval.eval) {
            maxEval = eval;
        }
        alpha = std::max(alpha, maxEval.eval);
        if (alpha >= beta) {
            killerHeuristic->AddKillerMove(childGameState.lastPerformedMove, childGameState.turnCount);
            break;
        }
    }
    return maxEval;
}