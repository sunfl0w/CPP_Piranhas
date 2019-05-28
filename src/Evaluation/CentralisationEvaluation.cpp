#include "CentralisationEvaluation.hpp"

using namespace Search::Evaluation;

CentralisationEvaluation::CentralisationEvaluation() {}

float CentralisationEvaluation::GetAverageCheckerValues(const std::vector<Field> &checkers) {
    float sumOfCheckerValues = GetSumOfCheckerValues(checkers);
    int checkerCount = checkers.size();
    float averageCheckerValues = sumOfCheckerValues;// / checkerCount;
    return averageCheckerValues;
}

float CentralisationEvaluation::GetSumOfCheckerValues(const std::vector<Field> &checkers) {
    int centralisationTable[] = {-2, -1, -1, -1, -1, -1, -1, -1, -1, -2,
                                 -1, 0, 0, 0, 0, 0, 0, 0, 0, -1,
                                 -1, 0, 1, 1, 1, 1, 1, 1, 0, -1,
                                 -1, 0, 1, 1, 1, 1, 1, 1, 0, -1,
                                 -1, 0, 1, 1, 1, 1, 1, 1, 0, -1,
                                 -1, 0, 1, 1, 1, 1, 1, 1, 0, -1,
                                 -1, 0, 1, 1, 1, 1, 1, 1, 0, -1,
                                 -1, 0, 1, 1, 1, 1, 1, 1, 0, -1,
                                 -1, 0, 0, 0, 0, 0, 0, 0, 0, -1,
                                 -2, -1, -1, -1, -1, -1, -1, -1, -1, -2};
    float sumOfValues = 0.0f;
    for (Field field : checkers) {
        sumOfValues += centralisationTable[(int)(field.position.y * 10 + field.position.x)];
    }
    return sumOfValues;
}

float CentralisationEvaluation::Evaluate(const std::vector<Field> &checkers) {
    return GetAverageCheckerValues(checkers);
}