#include "AI/Search/SearchAlgorithms/QuiescenceSearch.hpp"

using namespace AI::Search::SearchAlgorithms;
using namespace AI::Evaluation;
using namespace AI::Search::Helpers;
using namespace Piranhas;

QuiescenceSearch::QuiescenceSearch() {}

std::vector<GameState> QuiescenceSearch::GetChildGameStatesWithCaptures(const GameState &gameState) {
    std::vector<Move> possibleMoves = gameState.GetPossibleMoves();
    std::vector<GameState> childGameStatesPreviousCaptureMove;
    for (Move move : possibleMoves) {
        Position moveDestinationPos = gameState.board.GetDestinationPositionOfMove(move);
        if (gameState.board.GetField(moveDestinationPos).fieldType == gameState.currentPlayer.GetOppositePlayer().fieldType) {
            GameState childGameState = GameState(gameState);
            childGameState.PerformMove(move);
            childGameStatesPreviousCaptureMove.push_back(childGameState);
        }
    }
    return childGameStatesPreviousCaptureMove;
}

EvaluatedGameState QuiescenceSearch::Search(const GameState &gameState, unsigned int depth, float alpha, float beta, const SearchInformation &searchInformation) {
    float eval = Evaluator::EvaluateGameState(gameState);

    if(depth == 0 || gameState.IsGameOver() || std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - searchInformation.searchStartTimePoint).count() > searchInformation.maxSearchTimeInMs) {
        return EvaluatedGameState(gameState, eval);
    }

    if(eval >= beta) {
        return EvaluatedGameState(gameState, beta);
    }
    if(alpha < eval) {
        alpha = eval;
    }

    for(GameState childGameState : GetChildGameStatesWithCaptures(gameState)) {
        float captureEval = -Search(childGameState, depth - 1, -beta, -alpha, searchInformation).eval;

        if(captureEval >= beta) {
            return EvaluatedGameState(gameState, beta);
        }
        if(captureEval > alpha) {
            alpha = eval;
        }
    }
    return EvaluatedGameState(gameState, alpha);
}