#pragma once

#include <vector>

#include "Piranhas/PlayerColor.hpp"
#include "Piranhas/Player.hpp"
#include "Piranhas/Move.hpp"
#include "Piranhas/Board.hpp"
#include "Piranhas/GameResult.hpp"
#include "Piranhas/Constants/Constants.hpp"

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