#pragma once

namespace Piranhas {
    struct PositionF {
    public:
        float x, y;

        PositionF();
        PositionF(float x, float y);

        bool operator==(const PositionF &position) const;
        //bool operator!=(const Position &position) const;
    };
} // namespace Piranhas