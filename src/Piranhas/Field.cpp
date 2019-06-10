#include "Piranhas/Field.hpp"

#include "Piranhas/FieldType.hpp"
#include "Piranhas/Position.hpp"

using Piranhas::Field;

Field::Field() {
    this->fieldType = FieldType::Empty;
    this->position = Position(0,0);
}

Field::Field(FieldType fieldType, Position position) {
    this->fieldType = fieldType;
    this->position = position;
}

bool Field::IsChecker() const {
    if(fieldType == FieldType::Red || fieldType == FieldType::Blue) {
        return true;
    } else {
        return false;
    }
}

bool Field::operator==(const Field &field) const {
    if(fieldType != field.fieldType || position.x != field.position.x || position.y != field.position.y) {
        return false;
    } else {
        return true;
    }
}