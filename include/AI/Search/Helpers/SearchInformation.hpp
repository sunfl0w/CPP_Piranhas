#pragma once

#include <chrono>

#include "Piranhas/PlayerColor.hpp"

namespace AI::Search::Helpers {
    struct SearchInformation {
        Piranhas::PlayerColor ownPlayerColor;
        int maxSearchTimeInMs;
        std::chrono::high_resolution_clock::time_point searchStartTimePoint;
        unsigned int searchDepth;

        SearchInformation(Piranhas::PlayerColor ownPlayerColor, int maxSearchTimeInMs, std::chrono::high_resolution_clock::time_point searchStartTimePoint, unsigned int searchDepth) {
            this->ownPlayerColor = ownPlayerColor;
            this->maxSearchTimeInMs = maxSearchTimeInMs;
            this->searchStartTimePoint = searchStartTimePoint;
            this->searchDepth = searchDepth;
        }
    };
}