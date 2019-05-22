#include "UCB.hpp"

float Search::MCTS::UCB(MCTS_Node node, float explorationFactor) {
    return (float)node.wins / (float)node.visits + (float)explorationFactor * sqrt(log((float)node.parentNode->visits) / (float)node.visits);
}