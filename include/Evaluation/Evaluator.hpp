#pragma once

#include "GameState.hpp"
#include "ConcentrationEvaluation.hpp"
#include "CentralisationEvaluation.hpp"
#include "CenterOfMassEvaluation.hpp"
#include "ConnectednessEvaluation.hpp"
#include "UniformityEvaluation.hpp"

using namespace Piranhas;

namespace Search::Evaluation {
    class Evaluator {
    private:
        Evaluator();
        static float EvaluateEarlyGame(const GameState &gameState);
        static float EvaluateMidGame(const GameState &gameState);
        static float EvaluateEndGame(const GameState &gameState);

    public:
        static float EvaluateGameState(const GameState &gameState);
    };
} // namespace Search::Evaluation