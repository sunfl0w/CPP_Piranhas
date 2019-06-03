#include "ConcentrationEvaluation.hpp"

using namespace Search::Evaluation;
using namespace Piranhas;

ConcentrationEvaluation::ConcentrationEvaluation() {}

PositionF ConcentrationEvaluation::GetCenterOfMassPos(const std::vector<Field> &checkers) {
    float checkerTotalX = 0.0f;
    float checkerTotalY = 0.0f;
    for (Field field : checkers) {
        PositionF fieldPos = PositionF(field.position.x, field.position.y);
        checkerTotalX += fieldPos.x;
        checkerTotalY += fieldPos.y;
    }

    int checkerCount = checkers.size();

    float x = checkerTotalX / checkerCount;
    float y = checkerTotalY / checkerCount;
    return PositionF(x, y);
}

float ConcentrationEvaluation::GetSumOfDistancesToCenterOfMass(const std::vector<Field> &checkers, PositionF &centerOfMass) {
    float sumOfDistances = 0.0f;
    for (Field field : checkers) {
        sumOfDistances += std::sqrt(std::pow((centerOfMass.x - field.position.x), 2) + std::pow((centerOfMass.y - field.position.y), 2));
    }
    return sumOfDistances;
}

float ConcentrationEvaluation::GetSumOfMinimalDistanceToCenterOfMass(const std::vector<Field> &checkers) {
    float minimalSumOfDistancesToCenterOfMass[17] = {0, 0, 1, 2, 3, 4, 5.41f, 6.82f, 8.23f, 9.64f, 11.64f, 13.64f, 15.64f, 17.64f, 19.88f, 22.12f, 24.36f};
    int checkerCount = checkers.size();
    return minimalSumOfDistancesToCenterOfMass[checkerCount];
}

float ConcentrationEvaluation::Evaluate(const std::vector<Field> &checkers) {
    PositionF centerOfMass = GetCenterOfMassPos(checkers);
    float sumOfDistances = GetSumOfDistancesToCenterOfMass(checkers, centerOfMass);
    float sumOfMinimalDistances = GetSumOfMinimalDistanceToCenterOfMass(checkers);
    float surplusOfDistances = sumOfDistances - sumOfMinimalDistances;
    return surplusOfDistances * -1.0f;
}