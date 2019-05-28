#pragma once

#include <vector>

#include "FieldType.hpp"
#include "Field.hpp"
#include "Board.hpp"

using namespace Piranhas;

namespace Search::Evaluation {
    class ConnectednessEvaluation {
    private:
        ConnectednessEvaluation();
        static float GetAverageConnectionsOfCheckes(const std::vector<Field> &checkers, const Board &board);
    public:
        static float Evaluate(const std::vector<Field> &checkers, const Board &board);
    };
} // namespace Search::Evaluation