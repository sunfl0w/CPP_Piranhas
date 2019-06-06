#include "AI/Logic/Piranhas_MCTS_Logic.hpp"

using namespace AI::Logic;
using namespace Piranhas;
using namespace AI::Search::SearchAlgorithms::MCTS;

Piranhas_MCTS_Logic::Piranhas_MCTS_Logic(int searchTimeInMs) : PiranhasLogic(searchTimeInMs) {}

Move Piranhas_MCTS_Logic::GetNextMove(GameState currentGameState) {
    MCTS_Search mcts_Search = MCTS_Search(currentGameState.currentPlayer.color);
    Move bestMove = mcts_Search.GetNextMove(currentGameState, searchTimeInMs);
    return bestMove;
}