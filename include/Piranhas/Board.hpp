#pragma once

#include <array>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <memory>

#include "Piranhas/Direction.hpp"
#include "Piranhas/Field.hpp"
#include "Piranhas/FieldType.hpp"
#include "Piranhas/Move.hpp"
#include "Piranhas/Player.hpp"
#include "Piranhas/PlayerColor.hpp"
#include "Piranhas/Position.hpp"

namespace std {
    template <>
    struct hash<Piranhas::Field> {
        size_t operator()(const Piranhas::Field &field) const {
            hash<int> integerHasher;
            return integerHasher(field.position.x) ^ integerHasher(field.position.y) ^ integerHasher((int)field.fieldType);
        }
    };
} // namespace std

namespace Piranhas {
    class Board {
        std::array<Field, 100> fields;

    private:
        void SetCheckers();
        void SetObstacles();

        std::vector<Field> GetFieldsVertical(const Position &includedPos) const;
        std::vector<Field> GetFieldsHorizontal(const Position &includedPos) const;
        std::vector<Field> GetFieldsDownLeftUpRight(const Position &includedPos) const;
        std::vector<Field> GetFieldsDownRightUpLeft(const Position &includedPos) const;

        std::unordered_set<Field> GetSwarm(std::vector<Field> &found, std::unordered_set<Field> &swarm, int index) const;
        std::unordered_set<Field> GetGreatestSwarmFromParentSet(std::vector<Field> fieldsToSearch) const;
    public:
        int GetBiggestSwarmSizeTest(std::vector<Field> &checkers) const;

    public:
        Board();
        Board(Board &board);
        Board(const Board &board);

        void Print() const;

        void Populate();

        const Field& GetField(const Position &pos) const;
        const Field& GetField(int x, int y) const;
        
        void SetFieldTypeAtPosition(const Position &position, FieldType fieldType);
        void SetFieldTypeAtPosition(int x, int y, FieldType fieldType);

        bool IsPositionOnBoard(const Position &pos) const;

        std::vector<Field> GetNeighbouringFields(const Position &pos) const;
        std::vector<Field> GetNeighbouringFieldsOfType(const Position &pos, const std::vector<FieldType> &fieldTypeMask) const;

        Position GetMoveShiftPosition(Direction moveDir) const;

        std::vector<Field> GetFieldsMovePasses(const Move &move) const;
        std::vector<Field> GetFieldsMovePasses(const Move &move, const std::vector<Field> &fieldsInMoveDirection) const;
        std::vector<Field> GetFieldsMovePasses(const Position &moveStartPos, Direction moveDir, const std::vector<Field> &fieldsInMoveDirection) const;

        std::vector<Field> GetFieldsInDirection(const Position &includedPos, Direction direction) const;
        int GetFieldCountOfTypeInDirection(const Position &includedPos, const std::vector<FieldType> &fieldTypeMask, Direction direction) const;
        int GetCheckerCountInDirection(const Position &includedPos, Direction direction) const;
        int GetCheckerCountInDirection(const std::vector<Field> &fieldsInDirection) const;

        std::vector<Field> GetAllFieldsOfSameType(FieldType fieldType) const;

        int GetMoveDistance(const Move &move) const;
        int GetMoveDistance(const std::vector<Field> &fieldsInMoveDirection) const;

        Position GetDestinationPositionOfMove(const Move &move, int moveDistance) const;
        Position GetDestinationPositionOfMove(const Position &moveStartPos, Direction moveDir, int moveDistance) const;
        Position GetDestinationPositionOfMove(const Move &move) const;

        bool IsMovePathBlocked(const Move &move, FieldType blockingFieldType) const;
        bool IsMovePathBlocked(const Move &move, FieldType blockingFieldType, const std::vector<Field> &fieldsInMoveDirection) const;
        bool IsMovePathBlocked(const Position &moveStartPos, Direction moveDir, FieldType blockingFieldType, const std::vector<Field> &fieldsInMoveDirection) const;
        bool IsMovePathBlocked(const Move &move, int moveDistance, FieldType enemyFieldType) const;

        int GetBiggestSwarmSize(const Player &player) const;
        int GetBiggestSwarmSize(std::vector<Field> checkerFields) const;

        bool IsSwarmComplete(const Player &player) const;
        bool IsSwarmComplete(std::vector<Field> checkerFields) const;
        bool IsSwarmComplete(const Player &player, int swarmSize) const;
    };
} // namespace Piranhas
