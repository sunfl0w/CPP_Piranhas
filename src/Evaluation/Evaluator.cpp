#include "Evaluator.hpp"

using namespace Search::Evaluation;

Evaluator::Evaluator() {}

float Evaluator::EvaluateGameState(GameState gameState, PlayerColor maximizingPlayerColor, bool maximizing) {
    std::vector<Field> redFields = gameState.board.GetAllFieldsOfSameType(FieldType::Red);
    std::vector<Field> blueFields = gameState.board.GetAllFieldsOfSameType(FieldType::Blue);

    float redCheckerCount = redFields.size();
    float blueCheckerCount = blueFields.size();
    float materialEval = redCheckerCount - blueCheckerCount;

    float swarmEval = 0.0f;

    if (gameState.turnCount > 12) {
			int redSwarmSize = gameState.board.GetBiggestSwarmSize(redFields);
			int blueSwarmSize = gameState.board.GetBiggestSwarmSize(blueFields);
			swarmEval += (redSwarmSize / redCheckerCount - blueSwarmSize / blueCheckerCount) * 100.0f;
			if (gameState.turnCount > 26) {
				swarmEval += (redSwarmSize - blueSwarmSize) * 1.0f;
			}

			if (redSwarmSize == redCheckerCount) {
				swarmEval += 100.0f;
			}
			if (blueSwarmSize == blueCheckerCount) {
				swarmEval -= 100.0f;
			}
		}

    float eval = materialEval + swarmEval;

    if (maximizingPlayerColor == PlayerColor::Red) {
            if (maximizing) {
                return eval;
            } else {
                return -eval;
            }
        } else {
            if (maximizing) {
                return -eval;
            } else {
                return eval;
            }
        }
}