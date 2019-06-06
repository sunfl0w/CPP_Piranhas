#include "FullNegamaxSearch.hpp"

using namespace Search::Evaluation;
using namespace Search;
using namespace Search::Heuristics;
using namespace Client::Storage;

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
    if(transpositionTable->HasTransposition(gameState)) {
        Transposition transposition = transpositionTable->GetTransposition(gameState);
        if(transposition.depth >= depth) {
            if(transposition.flag == TranspositionFlag::Exact) {
                return EvaluatedGameState(gameState, transposition.eval);
            } else if(transposition.flag == TranspositionFlag::LowerBound) {
                alpha = std::max(alpha, transposition.eval);
            } else if(transposition.flag == TranspositionFlag::UpperBound) {
                beta = std::min(beta, transposition.eval);
            }
        }
        if(alpha >= beta) {
            return EvaluatedGameState(gameState, transposition.eval);
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

    std::vector<GameState> childGameStates = MoveOrdering::GetOrderedChildGameStates(gameState, searchInformation.ownPlayerColor, killerHeuristic, transpositionTable);
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
    if(transpositionTable->HasTransposition(gameState)) {
        Transposition transposition = transpositionTable->GetTransposition(gameState);
        transposition.eval = maxEval.eval;
        if(maxEval.eval <= originalAlpha) {
            transposition.flag = TranspositionFlag::UpperBound;
        } else if(maxEval.eval >= beta) {
            transposition.flag == TranspositionFlag::LowerBound;
        } else {
            transposition.flag == TranspositionFlag::Exact;
        }
        transposition.depth = depth;
        transposition.hashMove = maxEval.gameState.lastPerformedMove;
    } else {
        Transposition transposition = Transposition(0.0f, 0, TranspositionFlag::Exact, Move(maxEval.gameState.lastPerformedMove));
        transposition.eval = maxEval.eval;
        if(maxEval.eval <= originalAlpha) {
            transposition.flag = TranspositionFlag::UpperBound;
        } else if(maxEval.eval >= beta) {
            transposition.flag == TranspositionFlag::LowerBound;
        } else {
            transposition.flag == TranspositionFlag::Exact;
        }
        transposition.depth = depth;
        transpositionTable->AddTransposition(transpositionTable->ComputeKey(gameState), transposition);
    }

    return maxEval;
}