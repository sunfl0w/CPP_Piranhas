#pragma once

namespace Piranhas {
    struct Position {
    public:
        int x, y;

        Position();
        Position(int x, int y);

        bool operator==(const Position &position) const;
        //bool operator!=(const Position &position) const;
    };
} // namespace Piranhas