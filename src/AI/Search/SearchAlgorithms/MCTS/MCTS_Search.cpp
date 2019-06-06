#include "AI/Search/SearchAlgorithms/MCTS/MCTS_Search.hpp"

using namespace AI::Search::SearchAlgorithms::MCTS;
using namespace Piranhas;

MCTS_Search::MCTS_Search(PlayerColor maximizingPlayerColor) {
    this->maximizingPlayerColor = maximizingPlayerColor;
}

MCTS_Node *MCTS_Search::Select(MCTS_Node *mctsNode) {
    if (mctsNode->gameState.IsGameOver()) {
        return mctsNode;
    } else {
        if (!mctsNode->IsFullyExpanded()) {
            return mctsNode->GetNextUnvisitedChildNode();
        } else {
            return Select(mctsNode->GetBestChildNodeUCB());
        }
    }
}

MCTS_Node *MCTS_Search::Expand(MCTS_Node *mctsNode) {
    if (mctsNode->gameState.IsGameOver()) {
        return mctsNode;
    } else {
        if (!mctsNode->IsFullyExpanded()) {
            return mctsNode->GetNextUnvisitedChildNode();
        } else {
            return Select(mctsNode->GetBestChildNode());
        }
    }
}

bool MCTS_Search::Simulate(const MCTS_Node *expandedNode) {
    GameState gameState(expandedNode->gameState);

    srand(time(NULL));

    while (!gameState.IsGameOver()) {
        std::vector<Move> possibleMoves = gameState.GetPossibleMoves();
        Move nextMove = possibleMoves[rand() % possibleMoves.size()];
        gameState.PerformMove(nextMove);
    }

    GameResult gameResult = gameState.GetGameResult();
    if(maximizingPlayerColor == PlayerColor::Red && gameResult == GameResult::RedWin) {
        return true;
    } else if(maximizingPlayerColor == PlayerColor::Blue && gameResult == GameResult::BlueWin) {
        return true;
    } else {
        return false;
    }
}

void MCTS_Search::Backpropagate(MCTS_Node *expandedNode, bool simulationResult) {
    expandedNode->visits++;
    if (simulationResult) {
        expandedNode->wins++;
    }
    if (!expandedNode->IsParentNull()) {
        Backpropagate(expandedNode->parentNode, simulationResult);
    }
}

Move MCTS_Search::GetNextMove(GameState currentGameState, int searchTimeInMs) {
    std::chrono::high_resolution_clock::time_point startTimePoint = std::chrono::high_resolution_clock::now();

    MCTS_Node rootNode = MCTS_Node(currentGameState, NULL);

    //while (true) { 
    while(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTimePoint).count() < searchTimeInMs) {
        MCTS_Node *selectedNode = Select(&rootNode);
        //MCTS_Node *expandedNode = Expand(selectedNode);
        bool simulationResult = Simulate(selectedNode);
        Backpropagate(selectedNode, simulationResult);
    }

    std::cout << "Searched " << std::to_string(rootNode.visits - 1) << " nodes" << "\n";
    MCTS_Node bestChildNode = *rootNode.GetBestChildNode();
    return bestChildNode.gameState.lastPerformedMove;
}