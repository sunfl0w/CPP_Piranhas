#include "AI/Search/SearchAlgorithms/QuiescenceSearch.hpp"

using namespace AI::Search::SearchAlgorithms;
using namespace AI::Evaluation;
using namespace AI::Search::Helpers;
using namespace Piranhas;

QuiescenceSearch::QuiescenceSearch() {}

std::vector<Move> QuiescenceSearch::GetMovesWithCaptures(const GameState &gameState) {
    std::vector<Move> possibleMoves = gameState.GetPossibleMoves();
    std::vector<Move> captureMoves;
    for (Move move : possibleMoves) {
        Position moveDestinationPos = gameState.board.GetDestinationPositionOfMove(move);
        if (gameState.board.GetField(moveDestinationPos).fieldType == gameState.currentPlayer.GetOppositePlayer().fieldType) {
            captureMoves.push_back(move);
        }
    }
    return captureMoves;
}

EvaluatedGameState QuiescenceSearch::Search(GameState &gameState, unsigned int depth, float alpha, float beta, const SearchInformation &searchInformation) {
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

    for(Move move : GetMovesWithCaptures(gameState)) {
        gameState.PerformMove(move);
        float captureEval = -Search(gameState, depth - 1, -beta, -alpha, searchInformation).eval;
        gameState.RevertLastPerformedMove();
        nodesSearched++;

        if(captureEval >= beta) {
            return EvaluatedGameState(gameState, beta);
        }
        if(captureEval > alpha) {
            alpha = eval;
        }
    }
    return EvaluatedGameState(gameState, alpha);
}