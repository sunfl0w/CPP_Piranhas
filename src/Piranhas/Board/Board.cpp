#include <algorithm>
#include <array>
#include <functional>
#include <random>
#include <unordered_set>
#include <vector>

#include "Board.hpp"
#include "Field.hpp"
#include "FieldType.hpp"
#include "Move.hpp"
#include "Player.hpp"

using namespace Piranhas;

Board::Board() {
    bitboard = Bitboard();
}

Board::Board(Board &board) {
    Bitboard bitboard (board.bitboard);
    this->SetBitboard(bitboard);
}

Board::Board(const Board &board) {
    this->bitboard = Bitboard(board.bitboard);
}

void Board::Populate() {
    SetEmpty();
    SetCheckers();
    SetObstacles();
}

void Board::SetEmpty() {
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            SetFieldType(Position(x, y), FieldType::Empty);
        }
    }
}

void Board::SetCheckers() {
    for (int fieldIndex = 1; fieldIndex < 9; fieldIndex++) {
        SetField(Field(FieldType::Red, Position(0, fieldIndex)));

        SetField(Field(FieldType::Red, Position(9, fieldIndex)));

        SetField(Field(FieldType::Blue, Position(fieldIndex, 0)));

        SetField(Field(FieldType::Blue, Position(fieldIndex, 9)));
    }
}

void Board::SetObstacles() {
    std::random_device random;
    std::mt19937 randomEngine(random());
    std::uniform_int_distribution<> distribution(2, 7);

    int numberOfObstacles = 0;
    while (numberOfObstacles < 2) {
        Position randomPosition = Position(distribution(randomEngine), distribution(randomEngine));

        int obstaclesInLine = 0;
        obstaclesInLine += GetFieldCountOfTypeInDirection(randomPosition, std::vector<FieldType>{FieldType::Obstacle}, Direction::Up);
        obstaclesInLine += GetFieldCountOfTypeInDirection(randomPosition, std::vector<FieldType>{FieldType::Obstacle}, Direction::Left);
        obstaclesInLine += GetFieldCountOfTypeInDirection(randomPosition, std::vector<FieldType>{FieldType::Obstacle}, Direction::Down_Left);
        obstaclesInLine += GetFieldCountOfTypeInDirection(randomPosition, std::vector<FieldType>{FieldType::Obstacle}, Direction::Down_Right);

        if (obstaclesInLine == 0) {
            SetField(Field(FieldType::Obstacle, randomPosition));
            numberOfObstacles++;
        }
    }
}

std::vector<Field> Board::GetFieldsInDirection(const Position &includedPos, Direction direction) const {
    switch (direction) {
    case Direction::Up:
        return GetFieldsVertical(includedPos);
    case Direction::Down:
        return GetFieldsVertical(includedPos);
    case Direction::Right:
        return GetFieldsHorizontal(includedPos);
    case Direction::Left:
        return GetFieldsHorizontal(includedPos);
    case Direction::Down_Right:
        return GetFieldsDownRightUpLeft(includedPos);
    case Direction::Down_Left:
        return GetFieldsDownLeftUpRight(includedPos);
    case Direction::Up_Right:
        return GetFieldsDownLeftUpRight(includedPos);
    case Direction::Up_Left:
        return GetFieldsDownRightUpLeft(includedPos);
    default:
        std::vector<Field> empty;
        return empty;
    }
    std::vector<Field> empty;
    return empty;
}
std::vector<Field> Board::GetFieldsVertical(const Position &includedPos) const {
    std::vector<Field> fields;
    fields.reserve(10);
    for (int y = 0; y < 10; y++) {
        fields.push_back(GetField(includedPos.x, y));
    }
    return fields;
}
std::vector<Field> Board::GetFieldsHorizontal(const Position &includedPos) const {
    std::vector<Field> fields;
    fields.reserve(10);
    for (int x = 0; x < 10; x++) {
        fields.push_back(GetField(x, includedPos.y));
    }
    return fields;
}
std::vector<Field> Board::GetFieldsDownLeftUpRight(const Position &includedPos) const {
    std::vector<Field> fields;
    fields.reserve(10);
    int x = includedPos.x;
    int y = includedPos.y;

    while (x >= 0 && y >= 0) {
        fields.push_back(GetField(x, y));
        x--;
        y--;
    }

    x = includedPos.x + 1;
    y = includedPos.y + 1;

    while (x < 10 && y < 10) {
        fields.push_back(GetField(x, y));
        x++;
        y++;
    }
    return fields;
}
std::vector<Field> Board::GetFieldsDownRightUpLeft(const Position &includedPos) const {
    std::vector<Field> fields;
    fields.reserve(10);
    int x = includedPos.x;
    int y = includedPos.y;

    while (x < 10 && y >= 0) {
        fields.push_back(GetField(x, y));
        x++;
        y--;
    }

    x = includedPos.x - 1;
    y = includedPos.y + 1;

    while (x >= 0 && y < 10) {
        fields.push_back(GetField(x, y));
        x--;
        y++;
    }
    return fields;
}

std::unordered_set<Field> Board::GetSwarm(std::vector<Field> &found, std::unordered_set<Field> &swarm, int index) const {
    if (swarm.size() == 0 && found.size() > 0) {
        Field field = found[index];
        swarm.insert(field);
        /*std::vector<Field>::iterator iterator = std::find(found.begin(), found.end(), field);
        if(iterator != found.end()) {
            found.erase(iterator);
        }*/
        found.erase(std::remove(found.begin(), found.end(), field), found.end());
    }

    std::unordered_set<Field> tmpSwarm(swarm);
    for (Field field : swarm) {
        FieldType fieldType = field.fieldType;
        std::vector<Field> neighbours = GetNeighbouringFieldsOfType(field.position, std::vector<FieldType>{fieldType});
        for (Field neighbour : neighbours) {
            std::unordered_set<Field>::const_iterator iterator = tmpSwarm.find(neighbour);
            if (iterator == tmpSwarm.end()) { //Does not contain
                tmpSwarm.insert(neighbour);
            }
        }
    }

    if (swarm.size() != tmpSwarm.size()) {
        tmpSwarm = GetSwarm(found, tmpSwarm, index++);
    }

    for (Field tmpSwarmField : tmpSwarm) {
        std::unordered_set<Field>::const_iterator iterator = swarm.find(tmpSwarmField);
        if (iterator == swarm.end()) { //Does not contain
            swarm.insert(tmpSwarmField);
        }
    }

    for (Field swarmField : swarm) {
        found.erase(std::remove(found.begin(), found.end(), swarmField), found.end());
    }

    return swarm;
}

std::unordered_set<Field> Board::GetGreatestSwarmFromParentSet(std::vector<Field> fieldsToSearch) const {
    std::unordered_set<Field> greatestSwarm;
    int maxSize = 0;

    while (fieldsToSearch.size() > 0 && fieldsToSearch.size() > maxSize) {
        std::unordered_set<Field> empty;
        std::unordered_set<Field> swarm = GetSwarm(fieldsToSearch, empty, 0);
        if (maxSize < swarm.size()) {
            maxSize = swarm.size();
            greatestSwarm = swarm;
        }
    }
    return greatestSwarm;
}

int Board::GetFieldCountOfTypeInDirection(const Position &includedPos, const std::vector<FieldType> &fieldTypeMask, Direction direction) const {
    int count = 0;
    std::vector<Field> fieldsInDirection = std::vector<Field>(GetFieldsInDirection(includedPos, direction));
    for (Field field : fieldsInDirection) {
        for (FieldType maskType : fieldTypeMask) {
            if (field.fieldType == maskType) {
                count++;
            }
        }
    }
    return count;
}

int Board::GetCheckerCountInDirection(const Position &includedPos, Direction direction) const {
    int count = 0;
    std::vector<Field> fieldsInDirection = GetFieldsInDirection(includedPos, direction);
    for (Field field : fieldsInDirection) {
        if (field.IsChecker()) {
            count++;
        }
    }
    return count;
}

int Board::GetCheckerCountInDirection(const std::vector<Field> &fieldsInDirection) const {
    int count = 0;
    for (Field field : fieldsInDirection) {
        if (field.IsChecker()) {
            count++;
        }
    }
    return count;
}

Bitboard Board::GetBitboard() const {
    return bitboard;
}
void Board::SetBitboard(const Bitboard &bitboard) {
    this->bitboard = bitboard;
}

Field Board::GetField(const Position &position) const {
    return bitboard.GetField(position);
}
Field Board::GetField(int x, int y) const {
    //Position pos = Position(x,y);
    //Field field = bitboard.GetField(pos);
    return bitboard.GetField(Position(x, y));
}
void Board::SetField(Field field) {
    bitboard.SetField(field.position, field.fieldType);
}
void Board::SetFieldType(const Position &position, FieldType fieldType) {
    bitboard.SetField(position, fieldType);
}

bool Board::IsPositionOnBoard(const Position &position) const {
    return !(position.x < 0 || position.x > 9 || position.y < 0 || position.y > 9);
}

std::vector<Field> Board::GetNeighbouringFields(const Position &position) const {
    std::vector<Field> neighbouringFields;
    neighbouringFields.reserve(8);
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            int searchX = x + position.x;
            int searchY = y + position.y;
            if ((!(searchX == position.x && searchY == position.y)) && searchX >= 0 && searchY >= 0 && searchX < 10 && searchY < 10) {
                neighbouringFields.push_back(GetField(searchX, searchY));
            }
        }
    }
    return neighbouringFields;
}

std::vector<Field> Board::GetNeighbouringFieldsOfType(const Position &position, const std::vector<FieldType> &fieldTypeMask) const {
    std::vector<Field> neighbouringFields;
    neighbouringFields.reserve(8);
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            int searchX = x + position.x;
            int searchY = y + position.y;
            if ((!(searchX == position.x && searchY == position.y)) && searchX >= 0 && searchY >= 0 && searchX < 10 && searchY < 10) {
                for(FieldType fieldMask : fieldTypeMask) {
                    if(GetField(searchX, searchY).fieldType == fieldMask) {
                        neighbouringFields.push_back(GetField(searchX, searchY));
                    }
                }
            }
        }
    }
    return neighbouringFields;
}

std::vector<Field> Board::GetFieldsMovePasses(const Move &move) const {
    Position moveShiftPosition = move.GetShiftPosition();
    int moveDistance = GetMoveDistance(move);
    std::vector<Field> passedFields;
    passedFields.reserve(moveDistance);

    for (int i = 1; i < moveDistance; i++) {
        int x = move.GetStartPosition().x + moveShiftPosition.x * i;
        int y = move.GetStartPosition().y + moveShiftPosition.y * i;
        if (IsPositionOnBoard(Position(x, y))) {
            passedFields.push_back(GetField(x, y));
        }
    }
    return passedFields;
}

std::vector<Field> Board::GetFieldsMovePasses(const Move &move, const std::vector<Field> &fieldsInMoveDirection) const {
    Position moveShiftPosition = move.GetShiftPosition();
    int moveDistance = GetMoveDistance(move, fieldsInMoveDirection);
    std::vector<Field> passedFields;
    passedFields.reserve(moveDistance);

    for (int i = 1; i < moveDistance; i++) {
        int x = move.GetStartPosition().x + moveShiftPosition.x * i;
        int y = move.GetStartPosition().y + moveShiftPosition.y * i;
        if (IsPositionOnBoard(Position(x, y))) {
            passedFields.push_back(GetField(move.GetStartPosition().x + moveShiftPosition.x * i, move.GetStartPosition().y + moveShiftPosition.y * i));
        }
    }
    return passedFields;
}

std::vector<Field> Board::GetAllFieldsOfSameType(FieldType fieldType) const {
    std::vector<Field> fields;

    int size = 0;
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            if (GetField(x, y).fieldType == fieldType) {
                fields.push_back(GetField(x, y));
                size++;
            }
        }
    }
    return fields;
}

int Board::GetMoveDistance(const Move &move) const {
    return GetCheckerCountInDirection(move.GetStartPosition(), move.GetDirection());
}

int Board::GetMoveDistance(const Move &move, const std::vector<Field> &fieldsInMoveDirection) const {
    return GetCheckerCountInDirection(fieldsInMoveDirection);
}

Position Board::GetDestinationPositionOfMove(const Move &move, int moveDistance) const {
    Position destinationPos = move.GetStartPosition();

    switch (move.GetDirection()) {
    case Direction::Up:
        destinationPos.y += moveDistance;
        break;
    case Direction::Down:
        destinationPos.y -= moveDistance;
        break;
    case Direction::Right:
        destinationPos.x += moveDistance;
        break;
    case Direction::Left:
        destinationPos.x -= moveDistance;
        break;
    case Direction::Down_Right:
        destinationPos.x += moveDistance;
        destinationPos.y -= moveDistance;
        break;
    case Direction::Down_Left:
        destinationPos.x -= moveDistance;
        destinationPos.y -= moveDistance;
        break;
    case Direction::Up_Right:
        destinationPos.x += moveDistance;
        destinationPos.y += moveDistance;
        break;
    case Direction::Up_Left:
        destinationPos.x -= moveDistance;
        destinationPos.y += moveDistance;
        break;
    }
    return destinationPos;
}

Position Board::GetDestinationPositionOfMove(const Move &move) const{
    int moveDistance = GetMoveDistance(move);
    return GetDestinationPositionOfMove(move, moveDistance);
}

bool Board::IsMovePathBlocked(const Move &move, FieldType blockingFieldType) const {
    for (Field field : GetFieldsMovePasses(move)) {
        if (field.fieldType == blockingFieldType) {
            return true;
        }
    }
    return false;
}

bool Board::IsMovePathBlocked(const Move &move, FieldType blockingFieldType, const std::vector<Field> &fieldsInMoveDirection) const {
    for (Field field : GetFieldsMovePasses(move, fieldsInMoveDirection)) {
        if (field.fieldType == blockingFieldType) {
            return true;
        }
    }
    return false;
}

int Board::GetBiggestSwarmSize(const Player &player) const {
    std::vector<Field> checkerFields = GetAllFieldsOfSameType(player.fieldType);
    return GetBiggestSwarmSize(checkerFields);
}

int Board::GetBiggestSwarmSize(std::vector<Field> checkerFields) const {
    std::unordered_set<Field> swarmFields = GetGreatestSwarmFromParentSet(checkerFields);
    return swarmFields.size();
}

bool Board::IsSwarmComplete(const Player &player) const {
    std::vector<Field> checkerFields = GetAllFieldsOfSameType(player.fieldType);
    if (checkerFields.size() == GetBiggestSwarmSize(checkerFields)) {
        return true;
    } else {
        return false;
    }
}

bool Board::IsSwarmComplete(std::vector<Field> checkerFields) const {
    if (checkerFields.size() == GetBiggestSwarmSize(checkerFields)) {
        return true;
    } else {
        return false;
    }
}
