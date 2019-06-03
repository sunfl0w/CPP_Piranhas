#include "QuiescenceSearch.hpp"

using namespace Search;
using namespace Search::Evaluation;
using namespace Search::Helpers;
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

EvaluatedGameState QuiescenceSearch::Search(const GameState &gameState, unsigned int depth, float alpha, float beta, PlayerColor maximizingPlayerColor, bool maximizing) {
    float eval = Evaluator::EvaluateGameState(gameState, maximizingPlayerColor, maximizing);

    if(depth == 0 || gameState.IsGameOver()) {
        return EvaluatedGameState(gameState, eval);
    }

    if(eval >= beta) {
        return EvaluatedGameState(gameState, beta);
    }
    if(alpha < eval) {
        alpha = eval;
    }

    for(GameState childGameState : GetChildGameStatesWithCaptures(gameState)) {
        float captureEval = -Search(childGameState, depth - 1, -beta, -alpha, maximizingPlayerColor, !maximizing).eval;

        if(captureEval >= beta) {
            return EvaluatedGameState(gameState, beta);
        }
        if(captureEval > alpha) {
            alpha = eval;
        }
    }
    return EvaluatedGameState(gameState, alpha);
}