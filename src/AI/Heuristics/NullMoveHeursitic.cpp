#include "AI/Heuristics/NullMoveHeuristic.hpp"

using namespace AI::Heuristics;
using namespace Piranhas;
using namespace AI::Search::Helpers;
using namespace AI::Search::SearchAlgorithms;

NullMoveHeuristic::NullMoveHeuristic() {}

EvaluatedGameState NullMoveHeuristic::Search(const GameState &gameState, unsigned int depth, float alpha, float beta, bool maximizing, unsigned int depthReduction, const SearchInformation &searchInformation) {
    GameState clonedGameState(gameState);
    clonedGameState.SwapPlayers();
    clonedGameState.turnCount++;

    return EvaluatedGameState(GameState(gameState), -NegamaxSearch::Search(clonedGameState, depth - 1 - depthReduction, -beta, -beta + 1, !maximizing, searchInformation).eval);
}