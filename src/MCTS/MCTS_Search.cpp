#include "MCTS_Search.hpp"


MCTS_Node MCTS_Search::Select(const MCTS_Node &mctsNode) {
    if(!mctsNode.IsFullyExpanded()) {
        return mctsNode.GetNextUnvisitedChildNode();
    } else {
        return mctsNode.GetBestChildNode();
    }
}

MCTS_Node MCTS_Search::Expand(const MCTS_Node &leafNode) {

}

bool MCTS_Search::Simulate(const MCTS_Node &expandedNode) {

}

void MCTS_Search::Backpropagate(MCTS_Node &terminalNode) {

}

Move MCTS_Search::GetNextMove(GameState currentGameState) {

}