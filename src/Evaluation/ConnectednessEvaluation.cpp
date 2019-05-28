#include "ConnectednessEvaluation.hpp"

using namespace Search::Evaluation;
using namespace Piranhas;

ConnectednessEvaluation::ConnectednessEvaluation() {}

float ConnectednessEvaluation::GetAverageConnectionsOfCheckes(const std::vector<Field> &checkers, const Board &board) {
    int sumOfConnections = 0;
    std::vector<FieldType> fieldMask {checkers[0].fieldType};
    for (Field field : checkers) {
        sumOfConnections += board.GetNeighbouringFieldsOfType(field.position, fieldMask).size();
    }
    int checkerCount = checkers.size();
    return (float)sumOfConnections / checkerCount;
}

float ConnectednessEvaluation::Evaluate(const std::vector<Field> &checkers, const Board &board) {
    return GetAverageConnectionsOfCheckes(checkers, board);
}