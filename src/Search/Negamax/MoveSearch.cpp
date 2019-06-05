#include "MoveSearch.hpp"

using namespace Search;

MoveSearch::MoveSearch(int maxSearchTimeInMs, int maxSearchDepth) {
    this->maxSearchTimeInMs = maxSearchTimeInMs;
    this->maxSearchDepth = maxSearchDepth;
    this->killerHeursitic = KillerHeuristic();
    this->transpositionTable = TranspositionTable();
}

Move MoveSearch::SearchNextMove(GameState gameState, PlayerColor ownPlayerColor) {
    this->ownPlayerColor = ownPlayerColor;
    this->searchStartTimePoint = std::chrono::high_resolution_clock::now();

    FullNegamaxSearch fullNegamaxSearch = FullNegamaxSearch(&killerHeursitic, &transpositionTable);
    MinimaxSearch minimaxSearch;

    EvaluatedGameState nextBestGameState;

    int searchDepth = std::min(maxSearchDepth + 1, 61 - gameState.turnCount);

    std::cout << "Starting to search. Turn: " << std::to_string(gameState.turnCount) << "\n";

    int maxSearchDepthReached;

    for(int i = 1; i < searchDepth; i++) {
        EvaluatedGameState eval = fullNegamaxSearch.Search(gameState, i, -10000.0f, 10000.0f, SearchInformation(ownPlayerColor, maxSearchTimeInMs, searchStartTimePoint), true);
        //EvaluatedGameState eval = minimaxSearch.Search(gameState, i, true, SearchInformation(ownPlayerColor, maxSearchTimeInMs, searchStartTimePoint));
        if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - searchStartTimePoint).count() < maxSearchTimeInMs - 10) {
            nextBestGameState = eval;
            std::cout << "Reached layer: " << i << " || Time used: " << std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - searchStartTimePoint).count()) << "\n";
            std::cout << "Confidence: " << std::to_string(eval.eval) << "\n";
            maxSearchDepthReached = i;
        }
    }
    std::cout << "Stored transpositions: " << std::to_string(transpositionTable.GetSize()) << "\n";
    std::cout << "Nodes searched: " << std::to_string(fullNegamaxSearch.nodesSearched) << "\n";
    std::cout << "Average branching: " << std::to_string(std::pow(fullNegamaxSearch.nodesSearched, 1.0f / maxSearchDepthReached)) << "\n";
    return nextBestGameState.gameState.lastPerformedMove;
}