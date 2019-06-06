#pragma once

#include <vector>

#include "Piranhas/Board.hpp"
#include "Piranhas/Field.hpp"
#include "Piranhas/FieldType.hpp"

namespace AI::Evaluation {
    class ConnectednessEvaluation {
    private:
        ConnectednessEvaluation();
        static float GetAverageConnectionsOfCheckes(const std::vector<Piranhas::Field> &checkers, const Piranhas::Board &board);

    public:
        static float Evaluate(const std::vector<Piranhas::Field> &checkers, const Piranhas::Board &board);
    };
} // namespace AI::Evaluation