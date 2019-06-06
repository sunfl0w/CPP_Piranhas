#pragma once

namespace Piranhas {
    struct Position {
    public:
        unsigned char x, y;

        Position();
        Position(unsigned char x, unsigned char y);

        bool operator==(const Position &position) const;
        //bool operator!=(const Position &position) const;
    };
} // namespace Piranhas