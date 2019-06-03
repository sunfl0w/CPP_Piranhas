#pragma once

#include "CenterOfMassEvaluation.hpp"
#include "CentralisationEvaluation.hpp"
#include "ConcentrationEvaluation.hpp"
#include "ConnectednessEvaluation.hpp"
#include "GameState.hpp"
#include "UniformityEvaluation.hpp"

using namespace Piranhas;

namespace Search::Evaluation {
    class EvaluatorForMinimax {
    private:
        EvaluatorForMinimax();
        static float EvaluateEarlyGame(GameState gameState, PlayerColor maximizingPlayerColor) {
            Player maxPlayer(maximizingPlayerColor);
            Player minPlayer = maxPlayer.GetOppositePlayer();

            float eval = 0.0f;

            std::vector<Field> maxFields = gameState.board.GetAllFieldsOfSameType(maxPlayer.fieldType);
            std::vector<Field> minFields = gameState.board.GetAllFieldsOfSameType(minPlayer.fieldType);
            int maxCheckerCount = maxFields.size();
            int minCheckerCount = minFields.size();

            float materialEval = 0.0f;
            materialEval += (maxCheckerCount - minCheckerCount) * 3.0f;

            for (Move enemyMove : gameState.GetPossibleMoves()) {
                Position moveDestinationPos = gameState.board.GetDestinationPositionOfMove(enemyMove);
                if (gameState.board.GetField(moveDestinationPos).fieldType == gameState.GetOtherPlayer().fieldType) {
                    if (!(moveDestinationPos.x == 0 || moveDestinationPos.x == 9 || moveDestinationPos.y == 0 || moveDestinationPos.y == 9)) {
                        materialEval -= 1.0f;
                    }
                }
            }

            eval += materialEval;

            return eval;
        }
        static float EvaluateMidGame(GameState gameState, PlayerColor maximizingPlayerColor) {
            Player maxPlayer(maximizingPlayerColor);
            Player minPlayer = maxPlayer.GetOppositePlayer();

            float eval = 0.0f;

            std::vector<Field> maxFields = gameState.board.GetAllFieldsOfSameType(maxPlayer.fieldType);
            std::vector<Field> minFields = gameState.board.GetAllFieldsOfSameType(minPlayer.fieldType);
            int maxCheckerCount = maxFields.size();
            int minCheckerCount = minFields.size();

            float concentrationEval = (ConcentrationEvaluation::Evaluate(maxFields) - ConcentrationEvaluation::Evaluate(minFields)) * 0.1f;
            float centralisationEval = (CentralisationEvaluation::Evaluate(maxFields) - CentralisationEvaluation::Evaluate(minFields)) * 5.1f;
            float centerOfMassEval = (CenterOfMassEvaluation::Evaluate(maxFields) - CenterOfMassEvaluation::Evaluate(minFields)) * 1.0f;
            float connectednessEval = (ConnectednessEvaluation::Evaluate(maxFields, gameState.board) - ConnectednessEvaluation::Evaluate(minFields, gameState.board)) * 1.0f;
            float uniformityEval = (UniformityEvaluation::Evaluate(maxFields) - UniformityEvaluation::Evaluate(minFields)) * 5.0f;
            float materialEval = (maxCheckerCount - minCheckerCount) * 8.0f;

            for (Move enemyMove : gameState.GetPossibleMoves()) {
                Position moveDestinationPos = gameState.board.GetDestinationPositionOfMove(enemyMove);
                if (!(moveDestinationPos.x == 0 || moveDestinationPos.x == 9 || moveDestinationPos.y == 0 || moveDestinationPos.y == 9)) {
                    materialEval -= 1.8f;
                }
            }

            int maxSwarmSize = gameState.board.GetBiggestSwarmSize(maxFields);
            int minSwarmSize = gameState.board.GetBiggestSwarmSize(minFields);

            float swarmEval = (float)((float)maxSwarmSize / maxCheckerCount - (float)minSwarmSize / minCheckerCount) * 10.0f;
            if (gameState.turnCount > 40) {
                swarmEval += (maxSwarmSize - minSwarmSize) * 1.0f;
            }

            eval += swarmEval + materialEval + concentrationEval + centralisationEval + centerOfMassEval + connectednessEval + uniformityEval;

            return eval;
        }
        static float EvaluateEndGame(GameState gameState, PlayerColor maximizingPlayerColor) {
            Player maxPlayer(maximizingPlayerColor);
            Player minPlayer = maxPlayer.GetOppositePlayer();

            float eval = 0.0f;
            float swarmEval = 0.0f;

            std::vector<Field> maxFields = gameState.board.GetAllFieldsOfSameType(maxPlayer.fieldType);
            std::vector<Field> minFields = gameState.board.GetAllFieldsOfSameType(minPlayer.fieldType);
            int maxCheckerCount = maxFields.size();
            int minCheckerCount = minFields.size();
            int maxSwarmSize = gameState.board.GetBiggestSwarmSize(maxFields);
            int minSwarmSize = gameState.board.GetBiggestSwarmSize(minFields);

            swarmEval += (float)((float)maxSwarmSize / maxCheckerCount - (float)minSwarmSize / minCheckerCount) * 5.0f;
            if (gameState.turnCount > 40) {
                swarmEval += (maxSwarmSize - minSwarmSize) * 1.0f;
            }

            if (maxSwarmSize == maxCheckerCount) {
                swarmEval += 100.0f;
            }

            if (minSwarmSize == minCheckerCount) {
                swarmEval -= 100.0f;
            }

            eval += swarmEval;

            return eval;
        }

    public:
        static float EvaluateGameState(GameState gameState, PlayerColor maximizingPlayerColor) {
            float eval = 0.0f;
            if (gameState.turnCount < 8) {
                eval = EvaluateEarlyGame(gameState, maximizingPlayerColor);
            } else if (gameState.turnCount < 48) {
                eval = EvaluateMidGame(gameState, maximizingPlayerColor);
            } else {
                eval = EvaluateEndGame(gameState, maximizingPlayerColor);
            }
            return eval;
        }
    };
} // namespace Search::Evaluation