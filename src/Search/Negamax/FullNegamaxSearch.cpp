#include "FullNegamaxSearch.hpp"

using namespace Search::Evaluation;
using namespace Search;
using namespace Search::Heuristics;

FullNegamaxSearch::FullNegamaxSearch(KillerHeuristic *killerHeuristic) {
    this->killerHeuristic = killerHeuristic;
}

EvaluatedGameState FullNegamaxSearch::Search(const GameState &gameState, int depth, float alpha, float beta, bool maximizing, const SearchInformation &searchInformation) {
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - searchInformation.searchStartTimePoint).count() > searchInformation.maxSearchTimeInMs) {
        return EvaluatedGameState(gameState, 0.0f);
    }
    if (depth == 0 || gameState.IsGameOver()) {
        //float eval = Evaluator::EvaluateGameState(gameState, searchInformation.ownPlayerColor, maximizing);
        float eval = QuiescenceSearch::Search(gameState, 10, alpha, beta, searchInformation.ownPlayerColor, maximizing).eval;
        return EvaluatedGameState(gameState, eval);
    }

    /*if (depth > 2) {
        EvaluatedGameState nullMoveSearchEval = EvaluatedGameState(gameState, -NullMoveHeuristic::Search(gameState, depth, -beta, -alpha, !maximizing, 2, searchInformation).eval);
        if (nullMoveSearchEval.eval >= beta) {
            return nullMoveSearchEval;
        }
    }
    else if (depth > 1) {
        EvaluatedGameState nullMoveSearchEval = EvaluatedGameState(gameState, -NullMoveHeuristic::Search(gameState, depth, -beta, -alpha, !maximizing, 1, searchInformation).eval);
        if (nullMoveSearchEval.eval >= beta) {
            return nullMoveSearchEval;
        }
    }*/

    std::vector<GameState> childGameStates = MoveOrdering::GetOrderedChildGameStates(gameState, searchInformation.ownPlayerColor, killerHeuristic);
    EvaluatedGameState maxEval = EvaluatedGameState(childGameStates[0], -10000.0f);

    for (GameState childGameState : childGameStates) {
        EvaluatedGameState eval = EvaluatedGameState(childGameState, -(FullNegamaxSearch::Search(childGameState, depth - 1, -beta, -alpha, !maximizing, searchInformation).eval));
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