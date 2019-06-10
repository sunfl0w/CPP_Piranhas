#pragma once

#include <array>

#include "Piranhas/Move.hpp"
#include "Piranhas/Position.hpp"
#include "Piranhas/Direction.hpp"
#include "PerformedMove.hpp"
#include "Board.hpp"

namespace Piranhas {
    class MoveDistanceBoard {
        std::array<int, 10> moveDistancesUpDown;
        std::array<int, 10> moveDistancesLeftRight;
        std::array<int, 19> moveDistancesLowerLeftUpperRight;
        std::array<int, 19> moveDistancesLowerRightUpperLeft;

        int GetIndexUpDown(const Position &pos) const;
        int GetIndexLeftRight(const Position &pos) const;
        int GetIndexLowerLeftUpperRight(const Position &pos) const;
        int GetIndexLowerRightUpperLeft(const Position &pos) const;

    public:
        MoveDistanceBoard();
        MoveDistanceBoard(const Board &board);
        MoveDistanceBoard(MoveDistanceBoard &moveDistanceBoard);
        MoveDistanceBoard(const MoveDistanceBoard &moveDistanceBoard);

        void PerformMove(const Position &moveStartPos, const Position &moveDestinationPos, bool capture);
        void RevertMove(const PerformedMove &performedMove);
        int GetMoveDistance(const Move &move) const;
    };
} // namespace Piranhas