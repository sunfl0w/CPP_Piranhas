#include "AI/Search/SearchAlgorithms/NegaScoutSearch.hpp"

using namespace AI::Search::SearchAlgorithms;
using namespace AI::Search::Helpers;
using namespace AI::Transposition;
using namespace AI::Evaluation;
using namespace AI::MoveOrdering;
using namespace Piranhas;

NegaScoutSearch::NegaScoutSearch(AI::Heuristics::KillerHeuristic *killerHeuristic, AI::Transposition::TranspositionTable* transpositionTable) {
    this->killerHeuristic = killerHeuristic;
    this->transpositionTable = transpositionTable;
}

AI::Search::Helpers::EvaluatedGameState NegaScoutSearch::Search(const Piranhas::GameState &gameState, int depth, float alpha, float beta, const AI::Search::Helpers::SearchInformation &searchInformation, bool allowNullMove) {
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
    EvaluatedGameState alphaEval = EvaluatedGameState(childGameStates[0], alpha);
    for(int i = 0; i < childGameStates.size(); i++) {
        EvaluatedGameState eval;
        if(i == 0) {
            eval = EvaluatedGameState(childGameStates[i], -(NegaScoutSearch::Search(childGameStates[i], depth - 1, -beta, -alphaEval.eval, searchInformation, false).eval));
            nodesSearched++;
        } else {
            eval = EvaluatedGameState(childGameStates[i], -(NegaScoutSearch::Search(childGameStates[i], depth - 1, -alphaEval.eval - 1, -alphaEval.eval, searchInformation, false).eval));
            nodesSearched++;
            if(alpha < eval.eval && eval.eval < beta) {
                eval = EvaluatedGameState(childGameStates[i], -(NegaScoutSearch::Search(childGameStates[i], depth - 1, -beta, -eval.eval, searchInformation, false).eval));
                nodesSearched++;
            }
        }
        if(eval.eval > alphaEval.eval) {
            alphaEval = eval;
        }
        if(alpha >= beta) {
            break;
        }
    }

    //TranspositionTableLookup
    if(transpositionTable->HasTranspositionEntry(gameState)) {
        TranspositionEntry transpositionEntry = transpositionTable->GetTranspositionEntry(gameState);
        transpositionEntry.eval = alphaEval.eval;
        if(alphaEval.eval <= originalAlpha) {
            transpositionEntry.flag = TranspositionFlag::UpperBound;
        } else if(alphaEval.eval >= beta) {
            transpositionEntry.flag = TranspositionFlag::LowerBound;
        } else {
            transpositionEntry.flag = TranspositionFlag::Exact;
        }
        transpositionEntry.depth = depth;
        transpositionEntry.hashMove = alphaEval.gameState.lastPerformedMove;
    } else {
        TranspositionEntry transpositionEntry = TranspositionEntry(0.0f, 0, TranspositionFlag::Exact, Move(alphaEval.gameState.lastPerformedMove));
        transpositionEntry.eval = alphaEval.eval;
        if(alphaEval.eval <= originalAlpha) {
            transpositionEntry.flag = TranspositionFlag::UpperBound;
        } else if(alphaEval.eval >= beta) {
            transpositionEntry.flag = TranspositionFlag::LowerBound;
        } else {
            transpositionEntry.flag = TranspositionFlag::Exact;
        }
        transpositionEntry.depth = depth;
        transpositionTable->AddTranspositionEntry(transpositionTable->ComputeKey(gameState), transpositionEntry);
    }

    return alphaEval;
}