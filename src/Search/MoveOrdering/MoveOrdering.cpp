#include "MoveOrdering.hpp"

using namespace Piranhas;
using namespace Search;
using namespace Search::Helpers;

MoveOrdering::MoveOrdering() {}

float MoveOrdering::EvaluateMove(const Move &move, const GameState &gameState) {
    float moveEval = 0.0f;
    Position moveStartPos = move.GetStartPosition();
    Position moveDestinationPos = gameState.board.GetDestinationPositionOfMove(move);

    if (moveStartPos.x == 0 || moveStartPos.x == 9 || moveStartPos.y == 0 || moveStartPos.y == 9) {
        moveEval += 0.5f;
    }

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
        moveEval += 0.5f;
    }
    return moveEval;
}

std::vector<Move> MoveOrdering::GetOrderedPossibleMoves(const GameState &gameState, const PlayerColor maximizingPlayerColor) {
    std::vector<Move> movesToSearch = gameState.GetPossibleMoves();
    std::vector<EvaluatedMove> evaluatedMovesSorted;
    evaluatedMovesSorted.reserve(movesToSearch.size());

    for (Move move : movesToSearch) {
        float moveEval = EvaluateMove(move, gameState);
        evaluatedMovesSorted.push_back(EvaluatedMove(move, moveEval));
    }

    std::sort(evaluatedMovesSorted.begin(), evaluatedMovesSorted.end(), [](const auto &lhs, const auto &rhs) {
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

std::vector<Move> MoveOrdering::GetOrderedPossibleMoves(const GameState &gameState, const PlayerColor maximizingPlayerColor, const KillerHeuristic *killerHeuristic) {
    std::vector<Move> movesToSearch;

    std::vector<Move> validKillerMoves = killerHeuristic->GetValidKillerMoves(gameState);
    movesToSearch.insert(std::end(movesToSearch), std::begin(validKillerMoves), std::end(validKillerMoves));

    std::vector<Move> possibleMoves = gameState.GetPossibleMoves();
    movesToSearch.insert(std::end(movesToSearch), std::begin(possibleMoves), std::end(possibleMoves));

    std::vector<EvaluatedMove> evaluatedMovesSorted;
    evaluatedMovesSorted.reserve(movesToSearch.size());

    for (Move move : movesToSearch) {
        float moveEval = EvaluateMove(move, gameState);
        evaluatedMovesSorted.push_back(EvaluatedMove(move, moveEval));
    }

    std::sort(evaluatedMovesSorted.begin(), evaluatedMovesSorted.end(), [](const auto &lhs, const auto &rhs) {
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

std::vector<GameState> MoveOrdering::GetOrderedChildGameStates(const GameState &gameState, const PlayerColor maximizingPlayerColor) {
    std::vector<Move> movesToSearch = gameState.GetPossibleMoves();
    std::vector<Move> possibleMovesSorted = GetOrderedPossibleMoves(gameState, maximizingPlayerColor);

    std::vector<GameState> childGameStates;
    childGameStates.reserve(movesToSearch
                                .size());

    for (Move move : possibleMovesSorted) {
        GameState childGameState = GameState(gameState);
        childGameState.PerformMove(move);
        childGameStates.push_back(childGameState);
    }
    return childGameStates;
}

std::vector<GameState> MoveOrdering::GetOrderedChildGameStates(const GameState &gameState, const PlayerColor maximizingPlayerColor, const KillerHeuristic *killerHeuristic) {
    std::vector<Move> movesToSearch = gameState.GetPossibleMoves();
    std::vector<Move> possibleMovesSorted = GetOrderedPossibleMoves(gameState, maximizingPlayerColor, killerHeuristic);

    std::vector<GameState> childGameStates;
    childGameStates.reserve(movesToSearch
                                .size());

    for (Move move : possibleMovesSorted) {
        GameState childGameState = GameState(gameState);
        childGameState.PerformMove(move);
        childGameStates.push_back(childGameState);
    }
    return childGameStates;
}