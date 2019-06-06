#pragma once

#include <vector>

#include "Piranhas/Field.hpp"

namespace AI::Evaluation {
    class CentralisationEvaluation {
    private:
        CentralisationEvaluation();
        static float GetAverageCheckerValues(const std::vector<Piranhas::Field> &checkers);
        static float GetSumOfCheckerValues(const std::vector<Piranhas::Field> &checkers);

    public:
        static float Evaluate(const std::vector<Piranhas::Field> &checkers);
    };
} // namespace AI::Evaluation