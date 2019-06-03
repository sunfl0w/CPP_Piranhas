#pragma once

namespace Optimization {
    struct Range {
        float lowerBound, upperBound;

        Range(float lowerBound, float upperBound) {
            this->lowerBound = lowerBound;
            this->upperBound = upperBound;
        }
    };
}