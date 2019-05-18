#pragma once

#include <unordered_set>
#include <vector>
#include <array>

#include "Position.hpp"
#include "PlayerColor.hpp"
#include "Direction.hpp"
#include "FieldType.hpp"
#include "Move.hpp"
#include "Field.hpp"
#include "Player.hpp"

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
        void SetEmpty();
        void SetCheckers();
        void SetObstacles();

        std::vector<Field> GetFieldsVertical(const Position &includedPos);
        std::vector<Field> GetFieldsHorizontal(const Position &includedPos);
        std::vector<Field> GetFieldsDownLeftUpRight(const Position &includedPos);
        std::vector<Field> GetFieldsDownRightUpLeft(const Position &includedPos);

        std::unordered_set<Field> GetSwarm(std::vector<Field> &found, std::unordered_set<Field> &swarm, int index);
        std::unordered_set<Field> GetGreatestSwarmFromParentSet(std::vector<Field> fieldsToSearch); 

    public:
        Board();
        Board(Board &board);

        void Populate();

        std::array<Field, 100> GetFields();
        void SetFields(const std::array<Field, 100> &fields);

        const Field& GetField(const Position &pos) const;
        const Field& GetField(int x, int y) const;
        void SetField(Field field);
        void SetFieldType(const Position &position, FieldType fieldType);

        bool IsPositionOnBoard(const Position &pos);

        std::vector<Field> GetNeighbouringFields(const Position &pos);
        std::vector<Field> GetNeighbouringFieldsOfType(const Position &pos, const std::vector<FieldType> &fieldTypeMask);

        std::vector<Field> GetFieldsMovePasses(const Move &move);
        std::vector<Field> GetFieldsMovePasses(const Move &move, const std::vector<Field> &fieldsInMoveDirection);

        std::vector<Field> GetFieldsInDirection(const Position &includedPos, Direction direction);
        int GetFieldCountOfTypeInDirection(const Position &includedPos, const std::vector<FieldType> &fieldTypeMask, Direction direction);
        int GetCheckerCountInDirection(const Position &includedPos, Direction direction);
        int GetCheckerCountInDirection(const std::vector<Field> &fieldsInDirection);

        std::vector<Field> GetAllFieldsOfSameType(FieldType fieldType);

        int GetMoveDistance(const Move &move);
        int GetMoveDistance(const Move &move, const std::vector<Field> &fieldsInMoveDirection);
        Position GetDestinationPositionOfMove(const Move &move, int moveDistance);
        Position GetDestinationPositionOfMove(const Move &move);

        bool IsMovePathBlocked(const Move &move, FieldType blockingFieldType);
        bool IsMovePathBlocked(const Move &move, FieldType blockingFieldType, const std::vector<Field> &fieldsInMoveDirection);

        int GetBiggestSwarmSize(const Player &player);
        int GetBiggestSwarmSize(std::vector<Field> checkerFields);

        bool IsSwarmComplete(const Player &player);
        bool IsSwarmComplete(std::vector<Field> checkerFields);
    };
} // namespace Piranhas
