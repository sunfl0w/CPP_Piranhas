#include "Negamax_Search.hpp"

using namespace Search::Negamax;
using namespace Search::Evaluation;

Negamax_Search::Negamax_Search(PlayerColor maximizingPlayerColor, int maxSearchTimeInMs) {
    this->maximizingPlayerColor = maximizingPlayerColor;
    this->maxSearchTimeInMs = maxSearchTimeInMs;
}

std::vector<GameState> Negamax_Search::GetChildGameStatesSorted(GameState gameState) const {
    std::vector<Move> possibleMoves = gameState.GetPossibleMoves();
    std::vector<GameState> childGameStates;
    childGameStates.reserve(possibleMoves.size());

    for(Move move : possibleMoves) {
        GameState childGameState = GameState(gameState);
        childGameState.PerformMove(move);
        childGameStates.push_back(childGameState);
    }   
    return childGameStates;
}

Move Negamax_Search::GetNextMove(GameState currentGameState) {
    searchStartTimePoint = std::chrono::high_resolution_clock::now();

    GameState nextBestGameState;

    for (int i = 1; i < 10; i++) {
        EvaluatedGameState eval = RunNegamaxSearch(currentGameState, i, -10000.0f, 10000.0f, true);
        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - searchStartTimePoint).count() < maxSearchTimeInMs - 10) {
            nextBestGameState = eval.gameState;
            std::cout << "Reached layer: " << i << " || Time used: " << std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - searchStartTimePoint).count()) << "\n";
            std::cout << "Confidence: " << std::to_string(eval.eval) << "\n";
        }
    }
    return nextBestGameState.lastPerformedMove;
}

EvaluatedGameState Negamax_Search::RunNegamaxSearch(GameState gameState, int depth, float alpha, float beta, bool maximizing) {
    if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - searchStartTimePoint).count() > maxSearchTimeInMs) {
        return EvaluatedGameState(gameState, 0.0f);
    }
    if(depth == 0 || gameState.IsGameOver()) {
        float eval = Evaluator::EvaluateGameState(gameState, maximizingPlayerColor, maximizing);
        return EvaluatedGameState(gameState, eval);
    }

    std::vector<GameState> childGameStates = GetChildGameStatesSorted(gameState);
    EvaluatedGameState maxEval = EvaluatedGameState(childGameStates[0], -10000.0f);

    for(GameState childGameState : childGameStates) {
        EvaluatedGameState eval = EvaluatedGameState(childGameState, -(RunNegamaxSearch(childGameState, depth - 1, -beta, -alpha, !maximizing).eval));
        if(eval.eval > maxEval.eval) {
            maxEval = eval;
        }
        alpha = std::max(alpha, maxEval.eval);
        if(alpha >= beta) {
            break;
        }
    }
    return maxEval;
}