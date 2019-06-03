#include "Piranhas_Negamax_Logic.hpp"

using namespace Search;

Piranhas_Negamax_Logic::Piranhas_Negamax_Logic(int searchTimeInMs) : PiranhasLogic(searchTimeInMs) , moveSearch(searchTimeInMs, 6) {
}

Move Piranhas_Negamax_Logic::GetNextMove(GameState currentGameState, PlayerColor ownPlayerColor) {
    Move bestMove = moveSearch.SearchNextMove(currentGameState, ownPlayerColor);
    return bestMove;
}