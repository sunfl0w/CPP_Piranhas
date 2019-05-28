#include "CenterOfMassEvaluation.hpp"

using namespace Search::Evaluation;

CenterOfMassEvaluation::CenterOfMassEvaluation() {}

PositionF CenterOfMassEvaluation::GetCenterOfMassPos(const std::vector<Field> &checkers) {
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

float CenterOfMassEvaluation::Evaluate(const std::vector<Field> &checkers) {
    int centerOfMassTable[] = {-1, 0, 0, 0, 0, 0, 0, 0, 0, -1,
                               0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
                               0, 1, 1, 2, 2, 2, 2, 1, 1, 0,
                               0, 1, 2, 2, 2, 2, 2, 2, 1, 0,
                               0, 1, 2, 2, 1, 1, 2, 2, 1, 0,
                               0, 1, 2, 2, 1, 1, 2, 2, 1, 0,
                               0, 1, 2, 2, 2, 2, 2, 2, 1, 0,
                               0, 1, 1, 2, 2, 2, 2, 1, 1, 0,
                               0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
                               -1, 0, 0, 0, 0, 0, 0, 0, 0, -1};
    PositionF centerOfMassPos = GetCenterOfMassPos(checkers);
    return centerOfMassTable[(int)std::round(centerOfMassPos.y) * 10 + (int)std::round(centerOfMassPos.x)];
}