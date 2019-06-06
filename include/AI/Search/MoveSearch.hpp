#pragma once

#include <chrono>
#include <math.h>

#include "Piranhas/PlayerColor.hpp"
#include "Piranhas/GameState.hpp"
#include "AI/Search/Helpers/EvaluatedGameState.hpp"
#include "AI/Search/Helpers/SearchInformation.hpp"
#include "AI/Search/SearchAlgorithms/FullNegamaxSearch.hpp"
#include "AI/Search/SearchAlgorithms/MTDf.hpp"
#include "AI/Search/SearchAlgorithms/NegaScoutSearch.hpp"
#include "AI/Heuristics/KillerHeuristic.hpp"
#include "AI/Transposition/TranspositionTable.hpp"

namespace AI::Search {
    class MoveSearch {
    private:
        int maxSearchTimeInMs;
        Piranhas::PlayerColor ownPlayerColor;
        int maxSearchDepth;
        std::chrono::high_resolution_clock::time_point searchStartTimePoint;
        AI::Heuristics::KillerHeuristic killerHeursitic;
        AI::Transposition::TranspositionTable transpositionTable;

    public:
        MoveSearch(int maxSearchTimeInMs, int maxSearchDepth);

        Piranhas::Move SearchNextMove(Piranhas::GameState gameState, Piranhas::PlayerColor ownPlayerColor);
    };
} // namespace Search
