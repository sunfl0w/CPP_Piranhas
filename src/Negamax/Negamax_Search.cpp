#include "Negamax_Search.hpp"

using namespace Search::Negamax;
using namespace Search::Evaluation;

Negamax_Search::Negamax_Search(PlayerColor ownPlayerColor, std::chrono::high_resolution_clock::time_point searchStartTimePoint, int maxSearchTimeInMs) {
    this->ownPlayerColor = ownPlayerColor;
    this->maxSearchTimeInMs = maxSearchTimeInMs;
    this->searchStartTimePoint = searchStartTimePoint;
}

std::vector<GameState> Negamax_Search::GetChildGameStatesSorted(const GameState &gameState, PlayerColor maximizingPlayerColor) const {
    std::vector<Move> possibleMoves = gameState.GetPossibleMoves();
    std::vector<Move> possibleMovesSorted = GetPossibleMovesSorted(gameState, possibleMoves, maximizingPlayerColor);

    std::vector<GameState> childGameStates;
    childGameStates.reserve(possibleMoves.size());

    for (Move move : possibleMovesSorted) {
        GameState childGameState = GameState(gameState);
        childGameState.PerformMove(move);
        childGameStates.push_back(childGameState);
    }
    return childGameStates;
}

std::vector<Move> Negamax_Search::GetPossibleMovesSorted(const GameState &gameState, const std::vector<Move> &possibleMoves, PlayerColor maximizingPlayerColor) const {
    std::vector<EvaluatedMove> evaluatedMovesSorted;
    evaluatedMovesSorted.reserve(possibleMoves.size());

    for (Move move : possibleMoves) {
        float moveEval = 0.0f;
        Position moveDestinationPos = gameState.board.GetDestinationPositionOfMove(move);

            if (moveDestinationPos.x == 0 || moveDestinationPos.x == 9 || moveDestinationPos.y == 0 || moveDestinationPos.y == 9) {
            moveEval -= 1.5f;
        }
        if (moveDestinationPos.x > 0 && moveDestinationPos.x < 9 && moveDestinationPos.y > 0 && moveDestinationPos.y < 9) {
            moveEval += 1.5f;
        }
        if (moveDestinationPos.x > 1 && moveDestinationPos.x < 8 && moveDestinationPos.y > 1 && moveDestinationPos.y < 9) {
            moveEval += 1.5f;
        }

        if (gameState.board.GetField(moveDestinationPos).fieldType == gameState.GetOtherPlayer().fieldType) {
            moveEval += 2.5f;
        }
        evaluatedMovesSorted.push_back(EvaluatedMove(move, moveEval));
    }

    std::sort(evaluatedMovesSorted.begin(), evaluatedMovesSorted.end(), [](const auto& lhs, const auto& rhs) {
        return lhs.eval > rhs.eval;
    });

    float branching = 0.0f;
    if (gameState.currentPlayer.color != maximizingPlayerColor) {
        branching = 0.0f;
    }
    int originalSize = evaluatedMovesSorted.size();
    for (int i = 1; i <= originalSize * branching; i++) {
        evaluatedMovesSorted.erase(evaluatedMovesSorted.begin() + (originalSize - i));
    }

    std::vector<Move> movesSorted;
    movesSorted.reserve(evaluatedMovesSorted.size());
    for (EvaluatedMove move : evaluatedMovesSorted) {
        movesSorted.push_back(move.move);
    }

    return movesSorted;
}

EvaluatedGameState Negamax_Search::Negamax(const GameState &gameState, int depth, float alpha, float beta, bool maximizing) {
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - searchStartTimePoint).count() > maxSearchTimeInMs) {
        return EvaluatedGameState(gameState, 0.0f);
    }
    if (depth == 0 || gameState.IsGameOver()) {
        float eval = Evaluator::EvaluateGameState(gameState, ownPlayerColor, maximizing);
        return EvaluatedGameState(gameState, eval);
    }

    std::vector<GameState> childGameStates = GetChildGameStatesSorted(gameState, ownPlayerColor);
    EvaluatedGameState maxEval = EvaluatedGameState(childGameStates[0], -10000000.0f);

    for (GameState childGameState : childGameStates) {
        EvaluatedGameState eval = EvaluatedGameState(childGameState, -(Negamax(childGameState, depth - 1, -beta, -alpha, !maximizing).eval));
        if (eval.eval > maxEval.eval) {
            maxEval = eval;
        }
        alpha = std::max(alpha, maxEval.eval);
        if (alpha >= beta) {
            break;
        }
    }
    return maxEval;
}