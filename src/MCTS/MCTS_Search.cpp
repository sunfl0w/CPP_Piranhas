#include "MCTS_Search.hpp"


MCTS_Node MCTS_Search::Select(const MCTS_Node &mctsNode) {
    if(!mctsNode.IsFullyExpanded()) {
        return mctsNode;
    } else {
        return Select(mctsNode.GetBestChildNode());
    }
}

MCTS_Node MCTS_Search::Expand(const MCTS_Node &mctsNode) {
    if(mctsNode.gameState.IsGameOver()) {
        
    }
}

bool MCTS_Search::Simulate(const MCTS_Node &expandedNode) {

}

void MCTS_Search::Backpropagate(MCTS_Node &terminalNode) {

}

Move MCTS_Search::GetNextMove(GameState currentGameState) {

}