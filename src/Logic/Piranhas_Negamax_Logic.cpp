#include "Piranhas_Negamax_Logic.hpp"

using namespace Search::Negamax;

Piranhas_Negamax_Logic::Piranhas_Negamax_Logic(int searchTimeInMs) : PiranhasLogic(searchTimeInMs) {}

Move Piranhas_Negamax_Logic::GetNextMove(GameState currentGameState) {
    Negamax_Search negamax_Search = Negamax_Search(currentGameState.currentPlayer.color, searchTimeInMs);
    Move bestMove = negamax_Search.GetNextMove(currentGameState);
    return bestMove;
}