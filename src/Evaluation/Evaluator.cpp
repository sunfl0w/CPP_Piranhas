#include "Evaluator.hpp"

using namespace Search::Evaluation;

Evaluator::Evaluator() {}

float Evaluator::EvaluateGameState(const GameState &gameState) {
    float eval = 0.0f;
    if (gameState.turnCount < 0) {
        eval = EvaluateEarlyGame(gameState);
    } else if (gameState.turnCount < 60) {
        eval = EvaluateMidGame(gameState);
    } else {
        eval = EvaluateEndGame(gameState);
    }

    if (gameState.GetCurrentPlayer().color == PlayerColor::Red) {
        return eval;
    } else {
        return -eval;
    }
}

float Evaluator::EvaluateEarlyGame(const GameState &gameState) {
    float eval = 0.0f;

    std::vector<Field> redFields = gameState.board.GetAllFieldsOfSameType(FieldType::Red);
    std::vector<Field> blueFields = gameState.board.GetAllFieldsOfSameType(FieldType::Blue);
    int redCheckerCount = redFields.size();
    int blueCheckerCount = blueFields.size();

    int redInnerCheckerCount = 0;
    for (Field field : redFields) {
        if (field.position.x > 0 && field.position.x < 9 && field.position.y > 0 && field.position.y < 9) {
            redInnerCheckerCount++;
        }
    }

    int blueInnerCheckerCount = 0;
    for (Field field : blueFields) {
        if (field.position.x > 0 && field.position.x < 9 && field.position.y > 0 && field.position.y < 9) {
            blueInnerCheckerCount++;
        }
    }

    float materialEval = 0.0f;
    materialEval += (redCheckerCount - blueCheckerCount) * 3.0f;
    materialEval += (redInnerCheckerCount - blueInnerCheckerCount) * 1.0f;

    float vulnearbilityEval = 0.0f;

    /*for (Move enemyMove : gameState.GetPossibleMoves()) {
        Position moveDestinationPos = gameState.board.GetDestinationPositionOfMove(enemyMove);
        if (gameState.board.GetField(moveDestinationPos).fieldType == gameState.GetCurrentPlayer().GetOppositePlayer().fieldType) {
            if (moveDestinationPos.x > 0 && moveDestinationPos.x < 9 && moveDestinationPos.y > 0 && moveDestinationPos.y < 9) {
                vulnearbilityEval -= 1.8f;
            }
            if (moveDestinationPos.x > 2 && moveDestinationPos.x < 7 && moveDestinationPos.y > 2 && moveDestinationPos.y < 7) {
                vulnearbilityEval -= 1.8f;
            }
            if(moveDestinationPos.x == gameState.lastPerformedMoveDestinationPos.x && moveDestinationPos.y == gameState.lastPerformedMoveDestinationPos.y) {
                vulnearbilityEval -= 10.8f;
            }
        }
    }*/

    eval += materialEval + vulnearbilityEval;

    return eval;
}

float Evaluator::EvaluateMidGame(const GameState &gameState) {
    float eval = 0.0f;

    std::vector<Field> redFields = gameState.board.GetAllFieldsOfSameType(FieldType::Red);
    std::vector<Field> blueFields = gameState.board.GetAllFieldsOfSameType(FieldType::Blue);
    int redCheckerCount = redFields.size();
    int blueCheckerCount = blueFields.size();

    int redInnerCheckerCount = 0;
    for (Field field : redFields) {
        if (field.position.x > 0 && field.position.x < 9 && field.position.y > 0 && field.position.y < 9) {
            redInnerCheckerCount++;
        }
    }

    int blueInnerCheckerCount = 0;
    for (Field field : blueFields) {
        if (field.position.x > 0 && field.position.x < 9 && field.position.y > 0 && field.position.y < 9) {
            blueInnerCheckerCount++;
        }
    }

    float concentrationEval = (ConcentrationEvaluation::Evaluate(redFields) - ConcentrationEvaluation::Evaluate(blueFields)) * 0.3f;
    float centralisationEval = (CentralisationEvaluation::Evaluate(redFields) - CentralisationEvaluation::Evaluate(blueFields)) * 2.0f;
    float centerOfMassEval = (CenterOfMassEvaluation::Evaluate(redFields) - CenterOfMassEvaluation::Evaluate(blueFields)) * 1.0f;
    float connectednessEval = (ConnectednessEvaluation::Evaluate(redFields, gameState.board) - ConnectednessEvaluation::Evaluate(blueFields, gameState.board)) * 0.5f;
    float uniformityEval = (UniformityEvaluation::Evaluate(redFields) - UniformityEvaluation::Evaluate(blueFields)) * 5.0f;
    float materialEval = (redCheckerCount - blueCheckerCount) * 5.0f;

    int redSwarmSize = gameState.board.GetBiggestSwarmSize(redFields);
    int blueSwarmSize = gameState.board.GetBiggestSwarmSize(blueFields);

    float swarmEval = 0.0f;
    if (gameState.turnCount > 42) {
        swarmEval = (float)((float)redSwarmSize / redCheckerCount - (float)blueSwarmSize / blueCheckerCount) * 100.0f;
        if (gameState.turnCount > 26) {
            swarmEval += (redSwarmSize - blueSwarmSize) * 1.0f;
        }
    }

    eval += swarmEval + materialEval + concentrationEval + centralisationEval + centerOfMassEval + connectednessEval + uniformityEval;

    return eval;
}

float Evaluator::EvaluateEndGame(const GameState &gameState) {
    float eval = 0.0f;

    std::vector<Field> redFields = gameState.board.GetAllFieldsOfSameType(FieldType::Red);
    std::vector<Field> blueFields = gameState.board.GetAllFieldsOfSameType(FieldType::Blue);
    int redCheckerCount = redFields.size();
    int blueCheckerCount = blueFields.size();

    int redInnerCheckerCount = 0;
    for (Field field : redFields) {
        if (field.position.x > 0 && field.position.x < 9 && field.position.y > 0 && field.position.y < 9) {
            redInnerCheckerCount++;
        }
    }

    int blueInnerCheckerCount = 0;
    for (Field field : blueFields) {
        if (field.position.x > 0 && field.position.x < 9 && field.position.y > 0 && field.position.y < 9) {
            blueInnerCheckerCount++;
        }
    }

    float concentrationEval = (ConcentrationEvaluation::Evaluate(redFields) - ConcentrationEvaluation::Evaluate(blueFields)) * 0.1f;
    float centralisationEval = (CentralisationEvaluation::Evaluate(redFields) - CentralisationEvaluation::Evaluate(blueFields)) * 1.1f;
    float centerOfMassEval = (CenterOfMassEvaluation::Evaluate(redFields) - CenterOfMassEvaluation::Evaluate(blueFields)) * 1.0f;
    float connectednessEval = (ConnectednessEvaluation::Evaluate(redFields, gameState.board) - ConnectednessEvaluation::Evaluate(blueFields, gameState.board)) * 1.0f;
    float uniformityEval = (UniformityEvaluation::Evaluate(redFields) - UniformityEvaluation::Evaluate(blueFields)) * 10.0f;
    float materialEval = (redCheckerCount - blueCheckerCount) * 2.0f;

    int redSwarmSize = gameState.board.GetBiggestSwarmSize(redFields);
    int blueSwarmSize = gameState.board.GetBiggestSwarmSize(blueFields);

    float swarmEval = (float)((float)redSwarmSize / redCheckerCount - (float)blueSwarmSize / blueCheckerCount) * 50.0f;
    if (gameState.turnCount > 50) {
        swarmEval += (redSwarmSize - blueSwarmSize) * 2.0f;
    }

    eval += swarmEval + materialEval + concentrationEval + centralisationEval + centerOfMassEval + connectednessEval + uniformityEval;

    return eval;
}