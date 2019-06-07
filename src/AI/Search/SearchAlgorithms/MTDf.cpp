#include "AI/Search/SearchAlgorithms/MTDf.hpp"

using namespace AI::Search::SearchAlgorithms;
using namespace AI::Search::Helpers;

MTDfSearch::MTDfSearch(AI::Heuristics::KillerHeuristic *killerHeuristic, AI::Transposition::TranspositionTable *transpositionTable) {
    this->killerHeuristic = killerHeuristic;
    this->transpositionTable = transpositionTable;
}

AI::Search::Helpers::EvaluatedGameState MTDfSearch::Search(Piranhas::GameState &gameState, int depth, float guess, const AI::Search::Helpers::SearchInformation &searchInformation) {
    //FullNegamaxSearch fullNegamaxSearch = FullNegamaxSearch(killerHeuristic, transpositionTable);
    EvaluatedGameState maxEval = EvaluatedGameState(gameState, guess);

    float upperBound = 10000.0f;
    float lowerBound = -10000.0f;

    do {
        float beta;
        if (maxEval.eval == lowerBound) {
            beta = maxEval.eval + 1;
        } else {
            beta = maxEval.eval;
        }
        FullNegamaxSearch fullNegamaxSearch = FullNegamaxSearch(killerHeuristic, transpositionTable);
        maxEval = fullNegamaxSearch.Search(gameState, depth, beta - 1, beta, searchInformation, true);
        nodesSearched += fullNegamaxSearch.nodesSearched;
        if (maxEval.eval < beta) {
            upperBound = maxEval.eval;
        } else {
            lowerBound = maxEval.eval;
        }
    } while (lowerBound < upperBound);
    //nodesSearched = fullNegamaxSearch.nodesSearched;
    return maxEval;
}