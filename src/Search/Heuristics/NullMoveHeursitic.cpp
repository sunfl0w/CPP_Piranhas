#include "NullMoveHeuristic.hpp"

using namespace Search::Heuristics;

NullMoveHeuristic::NullMoveHeuristic() {}

EvaluatedGameState NullMoveHeuristic::Search(const GameState &gameState, unsigned int depth, float alpha, float beta, bool maximizing, unsigned int depthReduction, const SearchInformation &searchInformation) {
    GameState clonedGameState(gameState);
    clonedGameState.SwapPlayers();
    clonedGameState.turnCount++;

    return EvaluatedGameState(GameState(gameState), -NegamaxSearch::Search(clonedGameState, depth - 1 - depthReduction, -beta, -beta + 1, !maximizing, searchInformation).eval);
}