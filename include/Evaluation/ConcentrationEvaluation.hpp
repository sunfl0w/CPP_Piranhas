#pragma once

#include <vector>
#include <math.h>

#include "Field.hpp"
#include "PositionF.hpp"

using namespace Piranhas;

namespace Search::Evaluation {
    class ConcentrationEvaluation {
    private:
        ConcentrationEvaluation();
        static PositionF GetCenterOfMassPos(const std::vector<Field> &checkers);
        static float GetSumOfDistancesToCenterOfMass(const std::vector<Field> &checkers, PositionF &centerOfMass);
        static float GetSumOfMinimalDistanceToCenterOfMass(const std::vector<Field> &checkers);
    public:
        static float Evaluate(const std::vector<Field> &checkers);
    };
} // namespace Search::Evaluation