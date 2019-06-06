#pragma once

namespace Piranhas {
    struct Position {
    public:
        char x, y;

        Position();
        Position(char x, char y);

        bool operator==(const Position &position) const;
        //bool operator!=(const Position &position) const;
    };
} // namespace Piranhas