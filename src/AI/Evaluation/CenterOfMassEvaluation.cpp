#include "AI/Evaluation/CenterOfMassEvaluation.hpp"

using namespace AI::Evaluation;
using namespace Piranhas;

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
    int centerOfMassTable[100] = {-1, 0, 0, 0, 0, 0, 0, 0, 0, -1,
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
    int x = std::round(centerOfMassPos.x);
    int y = std::round(centerOfMassPos.y);

    if(x < 0) {
        x = 0;
    } else if(x > 9) {
        x = 9;
    }

    if(y < 0) {
        y = 0;
    } else if(y > 9) {
        y = 9;
    }

    float eval = centerOfMassTable[y * 10 + x];
    return eval;
}