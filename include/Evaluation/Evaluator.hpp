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
        static float EvaluateEarlyGame(GameState gameState, PlayerColor maximizingPlayerColor, bool maximizing);
        static float EvaluateMidGame(GameState gameState, PlayerColor maximizingPlayerColor, bool maximizing);
        static float EvaluateEndGame(GameState gameState, PlayerColor maximizingPlayerColor, bool maximizing);

    public:
        static float EvaluateGameState(GameState gameState, PlayerColor maximizingPlayerColor, bool maximizing);
    };
} // namespace Search::Evaluation