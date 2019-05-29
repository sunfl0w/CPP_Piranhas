#include "MoveSearch.hpp"

using namespace Search;
using namespace Search::Negamax;

MoveSearch::MoveSearch(int maxSearchTimeInMs, int maxSearchDepth) {
    this->maxSearchTimeInMs = maxSearchTimeInMs;
    this->maxSearchDepth = maxSearchDepth;
}

Move MoveSearch::SearchNextMove(GameState gameState, PlayerColor ownPlayerColor) {
    this->ownPlayerColor = ownPlayerColor;
    this->searchStartTimePoint = std::chrono::high_resolution_clock::now();

    /*std::vector<Field> redFields = gameState.board.GetAllFieldsOfSameType(FieldType::Red);
    std::vector<Field> blueFields = gameState.board.GetAllFieldsOfSameType(FieldType::Blue);
    float redCheckerCount = redFields.size();
    float blueCheckerCount = blueFields.size();
    int redSwarmSize = gameState.board.GetBiggestSwarmSize(redFields);
    int blueSwarmSize = gameState.board.GetBiggestSwarmSize(blueFields);

    std::cout << std::to_string(redSwarmSize) << " " << std::to_string(blueSwarmSize) << "\n";*/

    EvaluatedGameState nextBestGameState;

    int searchDepth = std::min(maxSearchDepth + 1, 61 - gameState.turnCount);

    std::cout << "Starting to search. Turn: " << std::to_string(gameState.turnCount) << "\n";

    for(int i = 1; i < searchDepth; i++) {
        Negamax_Search negamaxSearch = Negamax_Search(ownPlayerColor, searchStartTimePoint, maxSearchTimeInMs);
        EvaluatedGameState eval = negamaxSearch.Negamax(gameState, i, -1000000.0f, 1000000.0f, true);
        if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - searchStartTimePoint).count() < maxSearchTimeInMs - 10) {
            nextBestGameState = eval;
            std::cout << "Reached layer: " << i << " || Time used: " << std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - searchStartTimePoint).count()) << "\n";
            std::cout << "Confidence: " << std::to_string(eval.eval) << "\n";
        }
    }
    return nextBestGameState.gameState.lastPerformedMove;
}