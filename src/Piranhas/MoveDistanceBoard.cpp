#include "Piranhas/MoveDistanceBoard.hpp"

using namespace Piranhas;

MoveDistanceBoard::MoveDistanceBoard() {
    moveDistancesUpDown = std::array<int, 10>{8, 2, 2, 2, 2, 2, 2, 2, 2, 8};
    moveDistancesLeftRight = std::array<int, 10>{8, 2, 2, 2, 2, 2, 2, 2, 2, 8};
    moveDistancesLowerLeftUpperRight = std::array<int, 19>{0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0};
    moveDistancesLowerRightUpperLeft = std::array<int, 19>{0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0};
}

MoveDistanceBoard::MoveDistanceBoard(const Board &board) {
    moveDistancesUpDown = std::array<int, 10>();
    moveDistancesLeftRight = std::array<int, 10>();
    moveDistancesLowerLeftUpperRight = std::array<int, 19>();
    moveDistancesLowerRightUpperLeft = std::array<int, 19>();

    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            if (board.GetField(x, y).IsChecker()) {
                moveDistancesUpDown[GetIndexUpDown(board.GetField(x, y).position)] += 1;
                moveDistancesLeftRight[GetIndexLeftRight(board.GetField(x, y).position)] += 1;
                moveDistancesLowerLeftUpperRight[GetIndexLowerLeftUpperRight(board.GetField(x, y).position)] += 1;
                moveDistancesLowerRightUpperLeft[GetIndexLowerRightUpperLeft(board.GetField(x, y).position)] += 1;
            }
        }
    }
}

MoveDistanceBoard::MoveDistanceBoard(MoveDistanceBoard &moveDistanceBoard) {
    moveDistancesUpDown = moveDistanceBoard.moveDistancesUpDown;
    moveDistancesLeftRight = moveDistanceBoard.moveDistancesLeftRight;
    moveDistancesLowerLeftUpperRight = moveDistanceBoard.moveDistancesLowerLeftUpperRight;
    moveDistancesLowerRightUpperLeft = moveDistanceBoard.moveDistancesLowerRightUpperLeft;
}

MoveDistanceBoard::MoveDistanceBoard(const MoveDistanceBoard &moveDistanceBoard) {
    moveDistancesUpDown = moveDistanceBoard.moveDistancesUpDown;
    moveDistancesLeftRight = moveDistanceBoard.moveDistancesLeftRight;
    moveDistancesLowerLeftUpperRight = moveDistanceBoard.moveDistancesLowerLeftUpperRight;
    moveDistancesLowerRightUpperLeft = moveDistanceBoard.moveDistancesLowerRightUpperLeft;
}

int MoveDistanceBoard::GetIndexUpDown(const Position &pos) const {
    return pos.x;
}

int MoveDistanceBoard::GetIndexLeftRight(const Position &pos) const {
    return pos.y;
}

int MoveDistanceBoard::GetIndexLowerLeftUpperRight(const Position &pos) const {
    int borderX;
    int borderY;

    if (pos.y > pos.x) {
        borderY = pos.y - pos.x;
        borderX = 0;
    } else if (pos.x > pos.y) {
        borderX = pos.x - pos.y;
        borderY = 0;
    } else {
        borderX = 0;
        borderY = 0;
    }

    int index = 0;

    if (borderY > borderX) {
        index = 9 - borderY;
    } else if (borderY < borderX) {
        index = 9 + borderX;
    } else {
        index = 9;
    }

    return index;
}

int MoveDistanceBoard::GetIndexLowerRightUpperLeft(const Position &pos) const {
    int borderX;
    int borderY;

    int diffToMaximumX = 9 - pos.x;
    int diffToMinimumY = pos.y;

    if (diffToMinimumY > diffToMaximumX) {
        borderY = pos.y - diffToMaximumX;
        borderX = pos.x + diffToMaximumX;
    } else if (diffToMaximumX >= diffToMinimumY) {
        borderX = pos.x + diffToMinimumY;
        borderY = pos.y - diffToMinimumY;
    }

    int index = 0;

    if (borderX == 9) {
        index = 9 - borderY;
    } else if (borderY == 0) {
        index = -borderX + 18;
    }

    return index;
}

void MoveDistanceBoard::PerformMove(const Position &moveStartPos, const Position &moveDestinationPos, bool capture) {
    moveDistancesUpDown[GetIndexUpDown(moveStartPos)] -= 1;
    moveDistancesLeftRight[GetIndexLeftRight(moveStartPos)] -= 1;
    moveDistancesLowerLeftUpperRight[GetIndexLowerLeftUpperRight(moveStartPos)] -= 1;
    moveDistancesLowerRightUpperLeft[GetIndexLowerRightUpperLeft(moveStartPos)] -= 1;

    if (!capture) {
        moveDistancesUpDown[GetIndexUpDown(moveDestinationPos)] += 1;
        moveDistancesLeftRight[GetIndexLeftRight(moveDestinationPos)] += 1;
        moveDistancesLowerLeftUpperRight[GetIndexLowerLeftUpperRight(moveDestinationPos)] += 1;
        moveDistancesLowerRightUpperLeft[GetIndexLowerRightUpperLeft(moveDestinationPos)] += 1;
    }
}

void MoveDistanceBoard::RevertMove(const PerformedMove &performedMove) {
    moveDistancesUpDown[GetIndexUpDown(performedMove.move.GetStartPosition())] += 1;
    moveDistancesLeftRight[GetIndexLeftRight(performedMove.move.GetStartPosition())] += 1;
    moveDistancesLowerLeftUpperRight[GetIndexLowerLeftUpperRight(performedMove.move.GetStartPosition())] += 1;
    moveDistancesLowerRightUpperLeft[GetIndexLowerRightUpperLeft(performedMove.move.GetStartPosition())] += 1;

    if (!performedMove.isCapture) {
        moveDistancesUpDown[GetIndexUpDown(performedMove.destinationPos)] -= 1;
        moveDistancesLeftRight[GetIndexLeftRight(performedMove.destinationPos)] -= 1;
        moveDistancesLowerLeftUpperRight[GetIndexLowerLeftUpperRight(performedMove.destinationPos)] -= 1;
        moveDistancesLowerRightUpperLeft[GetIndexLowerRightUpperLeft(performedMove.destinationPos)] -= 1;
    }
}

int MoveDistanceBoard::GetMoveDistance(const Move &move) const {
    Direction dir = move.GetDirection();

    if (dir == Direction::Up || dir == Direction::Down) {
        return moveDistancesUpDown[GetIndexUpDown(move.GetStartPosition())];
    } else if (dir == Direction::Left || dir == Direction::Right) {
        return moveDistancesLeftRight[GetIndexLeftRight(move.GetStartPosition())];
    } else if (dir == Direction::Down_Left || dir == Direction::Up_Right) {
        return moveDistancesLowerLeftUpperRight[GetIndexLowerLeftUpperRight(move.GetStartPosition())];
    } else if (dir == Direction::Down_Right || dir == Direction::Up_Left) {
        return moveDistancesLowerRightUpperLeft[GetIndexLowerRightUpperLeft(move.GetStartPosition())];
    } else {
        return 0;
    }
}