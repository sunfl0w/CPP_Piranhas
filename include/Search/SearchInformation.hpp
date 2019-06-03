#pragma once

#include <chrono>

#include "PlayerColor.hpp"

using namespace Piranhas;

namespace Search {
    struct SearchInformation {
        PlayerColor ownPlayerColor;
        int maxSearchTimeInMs;
        std::chrono::high_resolution_clock::time_point searchStartTimePoint;

        SearchInformation(PlayerColor ownPlayerColor, int maxSearchTimeInMs, std::chrono::high_resolution_clock::time_point searchStartTimePoint) {
            this->ownPlayerColor = ownPlayerColor;
            this->maxSearchTimeInMs = maxSearchTimeInMs;
            this-> searchStartTimePoint = searchStartTimePoint;
        }
    };
}