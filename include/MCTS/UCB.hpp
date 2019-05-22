#pragma once

#include <math.h>

#include "MCTS_Node.hpp"

using namespace Search::MCTS;

namespace Search::MCTS {
    static float UCB(MCTS_Node node, float explorationFactor);
}