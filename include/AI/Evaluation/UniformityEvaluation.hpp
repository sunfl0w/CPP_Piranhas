#pragma once

#include <vector>

#include "Piranhas/Field.hpp"

namespace AI::Evaluation {
    class UniformityEvaluation {
    private:
        UniformityEvaluation();
        static float GetAreaCheckersCover(const std::vector<Piranhas::Field> &checkers);

    public:
        static float Evaluate(const std::vector<Piranhas::Field> &checkers);
    };
} // namespace AI::Evaluation