#pragma once

#include "AI/Evaluation/CenterOfMassEvaluation.hpp"
#include "AI/Evaluation/CentralisationEvaluation.hpp"
#include "AI/Evaluation/ConcentrationEvaluation.hpp"
#include "AI/Evaluation/ConnectednessEvaluation.hpp"
#include "AI/Evaluation/UniformityEvaluation.hpp"
#include "Piranhas/GameState.hpp"

namespace AI::Evaluation {
    class Evaluator {
    private:
        Evaluator();
        static float EvaluateEarlyGame(const Piranhas::GameState &gameState);
        static float EvaluateMidGame(const Piranhas::GameState &gameState);
        static float EvaluateEndGame(const Piranhas::GameState &gameState);

    public:
        static float EvaluateGameState(const Piranhas::GameState &gameState);
    };
} // namespace AI::Evaluation