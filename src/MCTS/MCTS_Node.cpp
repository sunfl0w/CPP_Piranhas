#include "MCTS_Node.hpp"

using namespace Search::MCTS;

MCTS_Node::MCTS_Node(const GameState &gameState, MCTS_Node* parentNode) {
    this->gameState = GameState(gameState);
    this->parentNode = parentNode;
}

void MCTS_Node::PopulateChildNodes() {
    for(Move move : gameState.GetPossibleMoves()) {
        GameState clonedGameState(gameState);
        clonedGameState.PerformMove(move);
        childNodes.push_back(new MCTS_Node(clonedGameState, this));
    }
}

float MCTS_Node::UCB(float explorationFactor) const {
    return (float)wins / (float)visits + (float)explorationFactor * sqrt(log((float)parentNode->visits) / (float)visits);
}

const bool MCTS_Node::IsParentNull() const {
    if(parentNode == NULL) {
        return true;
    } else {
        return false;
    }
}

const bool MCTS_Node::IsFullyExpanded() const {
    bool isFullyExpanded = true;
    if(childNodes.size() == 0) {
        return false;
    }
    for(MCTS_Node *childNode : childNodes) {
        if(childNode->visits == 0) {
            isFullyExpanded = false;
        }
    }
    return isFullyExpanded;
}

MCTS_Node *MCTS_Node::GetNextUnvisitedChildNode() {
    if(childNodes.size() == 0) {
        PopulateChildNodes();
    }
    for(MCTS_Node *childNode : childNodes) {
        if(childNode->visits == 0) {
            return childNode;
        }
    }
}

MCTS_Node *MCTS_Node::GetBestChildNode() {
    if(childNodes.size() == 0) {
        PopulateChildNodes();
    }
    MCTS_Node *bestNode = childNodes[0];
    for(MCTS_Node *childNode : childNodes) {
        if(childNode->visits > bestNode->visits) {
            bestNode = childNode;
        }
    }
    return bestNode;
}

MCTS_Node *MCTS_Node::GetBestChildNodeUCB() {
    if(childNodes.size() == 0) {
        PopulateChildNodes();
    }
    MCTS_Node *bestNode = childNodes[0];
    for(MCTS_Node *childNode : childNodes) {
        if(childNode->UCB(1.41f) > bestNode->UCB(1.41f)) {
            bestNode = childNode;
        }
    }
    return bestNode;
}