#include "AI/Search/SearchAlgorithms/FullNegamaxSearch.hpp"

using namespace AI::Evaluation;
using namespace AI::Search::SearchAlgorithms;
using namespace AI::Search::Helpers;
using namespace AI::MoveOrdering;
using namespace AI::Heuristics;
using namespace AI::Transposition;
using namespace Piranhas;

FullNegamaxSearch::FullNegamaxSearch(KillerHeuristic *killerHeuristic, TranspositionTable *transpositionTable) {
    this->killerHeuristic = killerHeuristic;
    this->transpositionTable = transpositionTable;
}

EvaluatedGameState FullNegamaxSearch::Search(const GameState &gameState, int depth, float alpha, float beta, const SearchInformation &searchInformation, bool allowNullMove) {
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - searchInformation.searchStartTimePoint).count() > searchInformation.maxSearchTimeInMs) {
        return EvaluatedGameState(gameState, 0.0f);
    }

    float originalAlpha = alpha;
    //TranspositionTableLookup
    if(transpositionTable->HasTranspositionEntry(gameState)) {
        TranspositionEntry transpositionEntry = transpositionTable->GetTranspositionEntry(gameState);
        if(transpositionEntry.depth >= depth) {
            if(transpositionEntry.flag == TranspositionFlag::Exact) {
                return EvaluatedGameState(gameState, transpositionEntry.eval);
            } else if(transpositionEntry.flag == TranspositionFlag::LowerBound) {
                alpha = std::max(alpha, transpositionEntry.eval);
            } else if(transpositionEntry.flag == TranspositionFlag::UpperBound) {
                beta = std::min(beta, transpositionEntry.eval);
            }
        }
        if(alpha >= beta) {
            return EvaluatedGameState(gameState, transpositionEntry.eval);
        }
    }


    if (depth == 0 || gameState.IsGameOver()) {
        float eval = Evaluator::EvaluateGameState(gameState);
        //float eval = QuiescenceSearch::Search(gameState, 10, alpha, beta, searchInformation).eval;
        return EvaluatedGameState(gameState, eval);
    }

    //NullMoveHeuristic
    if(allowNullMove && depth > 2 && gameState.turnCount < 46) {
        int r = 1;
        if(depth > 4) {
            r = 2;
        }

        GameState nullGameState = GameState(gameState);
        nullGameState.SwapPlayers();

        EvaluatedGameState nullEval = EvaluatedGameState(gameState, - Search(nullGameState, depth - r - 1, -beta, -beta + 1, searchInformation, false).eval);
        if(nullEval.eval >= beta) {
            return nullEval;
        }
    }
    //NullMoveHeuristic

    std::vector<GameState> childGameStates = MoveOrderer::GetOrderedChildGameStates(gameState, searchInformation.ownPlayerColor, killerHeuristic, transpositionTable);
    EvaluatedGameState maxEval = EvaluatedGameState(childGameStates[0], -10000.0f);
    for (GameState childGameState : childGameStates) {
        nodesSearched++;
        EvaluatedGameState eval = EvaluatedGameState(childGameState, -(FullNegamaxSearch::Search(childGameState, depth - 1, -beta, -alpha, searchInformation, true).eval));
        if (eval.eval > maxEval.eval) {
            maxEval = eval;
        }
        alpha = std::max(alpha, maxEval.eval);
        if (alpha >= beta) {
            killerHeuristic->AddKillerMove(childGameState.lastPerformedMove, childGameState.turnCount);
            break;
        }
    }

    //TranspositionTableLookup
    if(transpositionTable->HasTranspositionEntry(gameState)) {
        TranspositionEntry transpositionEntry = transpositionTable->GetTranspositionEntry(gameState);
        transpositionEntry.eval = maxEval.eval;
        if(maxEval.eval <= originalAlpha) {
            transpositionEntry.flag = TranspositionFlag::UpperBound;
        } else if(maxEval.eval >= beta) {
            transpositionEntry.flag = TranspositionFlag::LowerBound;
        } else {
            transpositionEntry.flag = TranspositionFlag::Exact;
        }
        transpositionEntry.depth = depth;
        transpositionEntry.hashMove = maxEval.gameState.lastPerformedMove;
    } else {
        TranspositionEntry transpositionEntry = TranspositionEntry(0.0f, 0, TranspositionFlag::Exact, Move(maxEval.gameState.lastPerformedMove));
        transpositionEntry.eval = maxEval.eval;
        if(maxEval.eval <= originalAlpha) {
            transpositionEntry.flag = TranspositionFlag::UpperBound;
        } else if(maxEval.eval >= beta) {
            transpositionEntry.flag == TranspositionFlag::LowerBound;
        } else {
            transpositionEntry.flag == TranspositionFlag::Exact;
        }
        transpositionEntry.depth = depth;
        transpositionTable->AddTranspositionEntry(transpositionTable->ComputeKey(gameState), transpositionEntry);
    }

    return maxEval;
}