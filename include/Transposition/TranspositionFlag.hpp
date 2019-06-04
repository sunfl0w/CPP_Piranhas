#pragma once

namespace Client::Storage {
    enum class TranspositionFlag
    {
        LowerBound,
        UpperBound,
        Exact,
    };
}