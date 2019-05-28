#pragma once

#include <math.h>
#include <vector>

#include "PositionF.hpp"
#include "Field.hpp"

using namespace Piranhas;

namespace Search::Evaluation {
    class CenterOfMassEvaluation {
    private:
        CenterOfMassEvaluation();
        static PositionF GetCenterOfMassPos(const std::vector<Field> &checkers);
    public:
        static float Evaluate(const std::vector<Field> &checkers);
    };
} // namespace Search::Evaluation