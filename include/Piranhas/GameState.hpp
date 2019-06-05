#pragma once

#include <vector>

#include "PlayerColor.hpp"
#include "Player.hpp"
#include "Move.hpp"
#include "Board.hpp"
#include "GameResult.hpp"

namespace Piranhas {
    class GameState {
    public:
        Board board;
        int turnCount;
        Player currentPlayer;
        Player startingPlayer;
        Move lastPerformedMove;
        Position lastPerformedMoveDestinationPos;

    public:
        GameState();
        GameState(PlayerColor startingPlayerColor);
        GameState(GameState &gameState);
        GameState(const GameState &gameState);

        void SwapPlayers();

        Player GetCurrentPlayer() const;
        Player GetOtherPlayer() const;

        bool IsMoveValid(Move &move) const;
        bool IsMoveValid(Move &move, std::vector<Field> &fieldsInMoveDirection) const;

        std::vector<Move> GetPossibleMoves() const;
        void PerformMove(Move &move);
        void RevertLastPerformedMove();

        bool IsGameOver() const;
        GameResult GetGameResult() const;
    };
} // namespace Piranhas