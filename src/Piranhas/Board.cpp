#include "Piranhas/Board.hpp"

#include <algorithm>
#include <array>
#include <functional>
#include <random>
#include <unordered_set>
#include <vector>

#include "Piranhas/Field.hpp"
#include "Piranhas/FieldType.hpp"
#include "Piranhas/Move.hpp"
#include "Piranhas/Player.hpp"

using namespace Piranhas;

Board::Board() {
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            fields[y * 10 + x].fieldType = FieldType::Empty;
            fields[y * 10 + x].position = Position(x, y);
        }
    }
}

Board::Board(Board &board) {
    this->fields = board.fields;
}

Board::Board(const Board &board) {
    this->fields = board.fields;
}

void Board::Populate() {
    SetCheckers();
    SetObstacles();
}

void Board::SetCheckers() {
    for (int fieldIndex = 1; fieldIndex < 9; fieldIndex++) {
        SetFieldTypeAtPosition(0, fieldIndex, FieldType::Red);
        SetFieldTypeAtPosition(9, fieldIndex, FieldType::Red);
        SetFieldTypeAtPosition(fieldIndex, 0, FieldType::Blue);
        SetFieldTypeAtPosition(fieldIndex, 9, FieldType::Blue);
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
            SetFieldTypeAtPosition(randomPosition, FieldType::Obstacle);
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
        //Field field = found[index];
        swarm.insert(found[index]);
        found.erase(std::remove(found.begin(), found.end(), found[index]), found.end());
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

int Board::GetBiggestSwarmSizeTest(std::vector<Field> &checkers) const {
    int maxSwarmSize = -100;
    FieldType fieldType = checkers[0].fieldType;
    std::unordered_map<int, Position> searchedPositions;

    for (Field checker : checkers) {
        int checkerCount = checkers.size();
        if(maxSwarmSize >= checkerCount / 2) {
            break;
        }
        std::vector<Position> searchQueue;
        int swarmSize = 0;
        if (checker.fieldType == fieldType && searchedPositions.find(checker.position.y * 10 + checker.position.x) == searchedPositions.end()) {
            swarmSize++;
            searchQueue.push_back(checker.position);
            searchedPositions[checker.position.y * 10 + checker.position.x] = checker.position;
        }
        while (!searchQueue.empty()) {
            Position searchPos = searchQueue[0];
            searchQueue.erase(searchQueue.begin());
            std::vector<Field> neighbours = GetNeighbouringFieldsOfType(searchPos, std::vector<FieldType>{fieldType});
            for (Field neighbour : neighbours) {
                if (neighbour.fieldType == fieldType && searchedPositions.find(neighbour.position.y * 10 + neighbour.position.x) == searchedPositions.end()) {
                    swarmSize++;
                    searchQueue.push_back(neighbour.position);
                    searchedPositions[neighbour.position.y * 10 + neighbour.position.x] = neighbour.position;
                }
            }
        }
        maxSwarmSize = std::max(maxSwarmSize, swarmSize);
    }
    return maxSwarmSize;
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

void Board::Print() const {
    for (int y = 9; y >= 0; y--) {
        for (int x = 0; x < 10; x++) {
            if (GetField(x, y).fieldType == FieldType::Red) {
                std::cout << "R";
            } else if (GetField(x, y).fieldType == FieldType::Blue) {
                std::cout << "B";
            } else if (GetField(x, y).fieldType == FieldType::Obstacle) {
                std::cout << "O";
            } else {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
}

const Field &Board::GetField(const Position &position) const {
    return fields[position.y * 10 + position.x];
}
const Field &Board::GetField(int x, int y) const {
    return fields[y * 10 + x];
}
void Board::SetFieldTypeAtPosition(const Position &position, FieldType fieldType) {
    fields[position.y * 10 + position.x].fieldType = fieldType;
}
void Board::SetFieldTypeAtPosition(int x, int y, FieldType fieldType) {
    fields[y * 10 + x].fieldType = fieldType;
}

bool Board::IsPositionOnBoard(const Position &position) const {
    return !(position.x < 0 || position.x > 9 || position.y < 0 || position.y > 9);
}

std::vector<Field> Board::GetNeighbouringFields(const Position &position) const {
    std::vector<Field> neighbouringFields;
    neighbouringFields.reserve(8);
    int searchX;
    int searchY;
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            searchX = x + position.x;
            searchY = y + position.y;
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
    int searchX;
    int searchY;
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            searchX = x + position.x;
            searchY = y + position.y;
            if (searchX == position.x && searchY == position.y) {
                continue;
            }
            if (searchX < 0 || searchY < 0 || searchX > 9 || searchY > 9) {
                continue;
            } else {
                for (FieldType fieldMask : fieldTypeMask) {
                    if (GetField(searchX, searchY).fieldType == fieldMask) {
                        neighbouringFields.push_back(GetField(searchX, searchY));
                    }
                }
            }
        }
    }
    return neighbouringFields;
}

Position Board::GetMoveShiftPosition(Direction moveDir) const {
    int shiftX = 0;
    int shiftY = 0;

    switch (moveDir) {
    case Direction::Up_Right:
        shiftX = 1;
        shiftY = 1;
        break;
    case Direction::Up:
        shiftY = 1;
        break;
    case Direction::Down_Right:
        shiftX = 1;
        shiftY = -1;
        break;
    case Direction::Right:
        shiftX = 1;
        break;
    case Direction::Down_Left:
        shiftX = -1;
        shiftY = -1;
        break;
    case Direction::Down:
        shiftY = -1;
        break;
    case Direction::Up_Left:
        shiftX = -1;
        shiftY = 1;
        break;
    case Direction::Left:
        shiftX = -1;
        break;
    }
    return Position(shiftX, shiftY);
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
    int moveDistance = GetMoveDistance(fieldsInMoveDirection);
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

std::vector<Field> Board::GetFieldsMovePasses(const Position &moveStartPos, Direction moveDir, const std::vector<Field> &fieldsInMoveDirection) const {
    Position moveShiftPosition = GetMoveShiftPosition(moveDir);
    int moveDistance = GetMoveDistance(fieldsInMoveDirection);
    std::vector<Field> passedFields;
    passedFields.reserve(moveDistance);

    for (int i = 1; i < moveDistance; i++) {
        int x = moveStartPos.x + moveShiftPosition.x * i;
        int y = moveStartPos.y + moveShiftPosition.y * i;
        if (IsPositionOnBoard(Position(x, y))) {
            passedFields.push_back(GetField(x, y));
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

int Board::GetMoveDistance(const std::vector<Field> &fieldsInMoveDirection) const {
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

Position Board::GetDestinationPositionOfMove(const Position &moveStartPos, Direction moveDir, int moveDistance) const {
    Position destinationPos = moveStartPos;

    switch (moveDir) {
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

Position Board::GetDestinationPositionOfMove(const Move &move) const {
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

bool Board::IsMovePathBlocked(const Position &moveStartPos, Direction moveDir, FieldType blockingFieldType, const std::vector<Field> &fieldsInMoveDirection) const {
    for (Field field : GetFieldsMovePasses(moveStartPos, moveDir, fieldsInMoveDirection)) {
        if (field.fieldType == blockingFieldType) {
            return true;
        }
    }
    return false;
}

bool Board::IsMovePathBlocked(const Move &move, int moveDistance, FieldType enemyFieldType) const {
    Position shiftPos = move.GetShiftPosition();
    Position moveStartPos = move.GetStartPosition();

    Field destinationfield = GetField(moveStartPos.x + moveDistance * shiftPos.x, moveStartPos.y + moveDistance * shiftPos.y);
            if(!(destinationfield.fieldType == FieldType::Empty || destinationfield.fieldType == enemyFieldType)) {
                return true;
            } 
        

    for(int i = 1; i < moveDistance; i++) {
        /*if(i < moveDistance && GetField(move.GetStartPosition().x + i * shiftPos.x, move.GetStartPosition().y + i * shiftPos.y).fieldType == enemyFieldType) {
            return true;
        }
        if(i == moveDistance) {
            if(GetField(move.GetStartPosition().x + i * shiftPos.x, move.GetStartPosition().y + i * shiftPos.y).fieldType == FieldType::Empty || GetField(move.GetStartPosition().x + i * shiftPos.x, move.GetStartPosition().y + i * shiftPos.y).fieldType == enemyFieldType) {
                return false;
            } else {
                return true;
            }
        }*/
        Field field = GetField(moveStartPos.x + i * shiftPos.x, moveStartPos.y + i * shiftPos.y);
        if(i < moveDistance && field.fieldType == enemyFieldType) {
            return true;
        }
        /*if(i == moveDistance) {
            if(field.fieldType == FieldType::Empty || field.fieldType == enemyFieldType) {
                return false;
            } else {
                return true;
            }
        }*/
    }
    return false;
}

int Board::GetBiggestSwarmSize(const Player &player) const {
    std::vector<Field> checkerFields = GetAllFieldsOfSameType(player.fieldType);
    //return GetBiggestSwarmSize(checkerFields);
    return GetBiggestSwarmSizeTest(checkerFields);
}

int Board::GetBiggestSwarmSize(std::vector<Field> checkerFields) const {
    //std::unordered_set<Field> swarmFields = GetGreatestSwarmFromParentSet(checkerFields);
    //return swarmFields.size();
    return GetBiggestSwarmSizeTest(checkerFields);
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

bool Board::IsSwarmComplete(const Player &player, int swarmSize) const {
    std::vector<Field> checkerFields = GetAllFieldsOfSameType(player.fieldType);
    if (checkerFields.size() == swarmSize) {
        return true;
    } else {
        return false;
    }
}
