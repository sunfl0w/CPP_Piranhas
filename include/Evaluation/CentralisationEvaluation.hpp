#pragma once

#include <vector>

#include "Field.hpp"

using namespace Piranhas;

namespace Search::Evaluation {
    class CentralisationEvaluation {
    private:
        CentralisationEvaluation();
        static float GetAverageCheckerValues(const std::vector<Field> &checkers);
        static float GetSumOfCheckerValues(const std::vector<Field> &checkers);
    public:
        static float Evaluate(const std::vector<Field> &checkers);
    };
} // namespace Search::Evaluation