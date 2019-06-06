#pragma once

#include <functional>

#include "Piranhas/FieldType.hpp"
#include "Piranhas/Position.hpp"

namespace Piranhas {
    struct Field {
    public:
        Position position;
        FieldType fieldType;

        Field();
        Field(FieldType fieldType, Position position);

        bool IsChecker();

        bool operator==(const Field &field) const;
    };
} // namespace Piranhas

/*namespace std {
    template <>
    struct hash<Piranhas::Field> {
        size_t operator()(const Piranhas::Field &field) const {
            hash<int> integerHasher;
            return integerHasher(field.position.x) ^ integerHasher(field.position.y) ^ integerHasher((int)field.fieldType);
        }
    };
}*/ // namespace std