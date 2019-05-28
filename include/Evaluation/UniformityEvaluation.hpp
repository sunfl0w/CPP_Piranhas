#pragma once

#include <vector>

#include "Field.hpp"

using namespace Piranhas;

namespace Search::Evaluation {
    class UniformityEvaluation {
    private:
        UniformityEvaluation();
        static float GetAreaCheckersCover(const std::vector<Field> &checkers);
    public:
        static float Evaluate(const std::vector<Field> &checkers);
    };
} // namespace Search::Evaluation