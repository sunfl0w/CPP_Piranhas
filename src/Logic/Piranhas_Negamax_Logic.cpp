#include "Piranhas_Negamax_Logic.hpp"

using namespace Search::Negamax;
using namespace Search;

Piranhas_Negamax_Logic::Piranhas_Negamax_Logic(int searchTimeInMs) : PiranhasLogic(searchTimeInMs) {}

Move Piranhas_Negamax_Logic::GetNextMove(GameState currentGameState, PlayerColor ownPlayerColor) {
    MoveSearch moveSearch = MoveSearch(searchTimeInMs, 6);
    Move bestMove = moveSearch.SearchNextMove(currentGameState, ownPlayerColor);
    return bestMove;
}