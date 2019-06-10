#include "AI/Search/MoveSearch.hpp"

using namespace AI::Search;
using namespace AI::Search::SearchAlgorithms;
using namespace AI::Search::Helpers;
using namespace AI::Heuristics;
using namespace AI::Transposition;
using namespace Piranhas;

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
    MTDfSearch mtdfSearch = MTDfSearch(&killerHeursitic, &transpositionTable);
    NegaScoutSearch negaScoutSearch = NegaScoutSearch(&killerHeursitic, &transpositionTable);

    std::vector<EvaluatedGameState> nextBestGameStates;

    int searchDepth = maxSearchDepth;

    std::cout << "Starting to search. Turn: " << std::to_string(gameState.turnCount) << "\n";

    int maxSearchDepthReached;

    float lastEvalEven = 0.0f;
    float lastEvalOdd = 0.0f;

    for(int i = 1; i < searchDepth; i++) {
        /*EvaluatedGameState eval = fullNegamaxSearch.Search(gameState, i, -10000.0f, 10000.0f, SearchInformation(ownPlayerColor, maxSearchTimeInMs, searchStartTimePoint), true);
        if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - searchStartTimePoint).count() < maxSearchTimeInMs - 10) {
            nextBestGameState = eval;
            std::cout << "Reached layer: " << i << " || Time used: " << std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - searchStartTimePoint).count()) << "\n";
            std::cout << "Confidence: " << std::to_string(eval.eval) << "\n";
            maxSearchDepthReached = i;
        }*/
        float guess = 0.0f;
        if(i % 2 == 0) {
            guess = lastEvalEven;
        } else {
            guess = lastEvalOdd;
        }

        EvaluatedGameState eval = mtdfSearch.Search(gameState, i, guess, SearchInformation(ownPlayerColor, maxSearchTimeInMs, searchStartTimePoint, i));
        if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - searchStartTimePoint).count() < maxSearchTimeInMs - 10) {
            nextBestGameStates.push_back(eval);
            std::cout << "Reached layer: " << i << " || Time used: " << std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - searchStartTimePoint).count()) << "\n";
            std::cout << "Confidence: " << std::to_string(eval.eval) << "\n";
            maxSearchDepthReached = i;
        }
        if(i % 2 == 0) {
            lastEvalEven = nextBestGameStates[nextBestGameStates.size() - 1].eval;
        } else {
            lastEvalOdd = nextBestGameStates[nextBestGameStates.size() - 1].eval;
        }
        /*EvaluatedGameState eval = negaScoutSearch.Search(gameState, i, -10000.0f, 10000.0f, SearchInformation(ownPlayerColor, maxSearchTimeInMs, searchStartTimePoint), true);
        if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - searchStartTimePoint).count() < maxSearchTimeInMs - 10) {
            nextBestGameState = eval;
            std::cout << "Reached layer: " << i << " || Time used: " << std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - searchStartTimePoint).count()) << "\n";
            std::cout << "Confidence: " << std::to_string(eval.eval) << "\n";
            maxSearchDepthReached = i;
        }*/
    }
    std::cout << "Stored transpositions: " << std::to_string(transpositionTable.GetSize()) << "\n";
    std::cout << "Nodes searched: " << std::to_string(mtdfSearch.nodesSearched) << "\n";
    std::cout << "Average branching: " << std::to_string(std::pow(mtdfSearch.nodesSearched, 1.0f / maxSearchDepthReached)) << "\n";  

    Move bestMove = nextBestGameStates[nextBestGameStates.size() - 1].gameState.GetLastPerformedMove();
    if(bestMove.GetStartPosition().x == 0 && bestMove.GetStartPosition().y == 0 && bestMove.GetDirection() == Direction::Up) {
        std::cout << "No move found? Going through previous iterations." << "\n";
        for(int i = nextBestGameStates.size() - 2; i >= 0; i--) {
            Move altMove = nextBestGameStates[i].gameState.GetLastPerformedMove();
            if(altMove.GetStartPosition().x == 0 && altMove.GetStartPosition().y == 0 && altMove.GetDirection() == Direction::Up) {
                std::cout << "Alt move not found either?" << "\n";
                continue;
            } else {
                return altMove;
            }
        }
    } else {
        return bestMove;
    }
}