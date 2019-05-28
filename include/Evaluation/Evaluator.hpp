#pragma once

#include "GameState.hpp"
#include "CentralisationEvaluation.hpp"
#include "CenterOfMassEvaluation.hpp"
#include "ConnectednessEvaluation.hpp"
#include "UniformityEvaluation.hpp"

using namespace Piranhas;

namespace Search::Evaluation {
    class Evaluator {
    private:
        Evaluator();

    public:
        static float EvaluateGameState(GameState gameState, PlayerColor maximizingPlayerColor, bool maximizing);
    };
} // namespace Search::Evaluation