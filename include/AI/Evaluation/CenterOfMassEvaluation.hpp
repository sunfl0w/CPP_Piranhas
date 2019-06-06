#pragma once

#include <math.h>
#include <vector>

#include "Piranhas/Field.hpp"
#include "Piranhas/PositionF.hpp"

namespace AI::Evaluation {
    class CenterOfMassEvaluation {
    private:
        CenterOfMassEvaluation();
        static Piranhas::PositionF GetCenterOfMassPos(const std::vector<Piranhas::Field> &checkers);

    public:
        static float Evaluate(const std::vector<Piranhas::Field> &checkers);
    };
} // namespace AI::Evaluation