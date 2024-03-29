#pragma once

#include <vector>
#include <array>

#include "Piranhas/PlayerColor.hpp"
#include "Piranhas/Player.hpp"
#include "Piranhas/Move.hpp"
#include "Piranhas/Board.hpp"
#include "Piranhas/GameResult.hpp"
#include "Piranhas/Constants/Constants.hpp"
#include "Piranhas/PerformedMove.hpp"
#include "Piranhas/MoveDistanceBoard.hpp"

namespace Piranhas {
    class GameState {
    public:
        Board board;
        MoveDistanceBoard moveDistanceBoard;
        int turnCount;
        Player currentPlayer;
        Player startingPlayer;
        std::array<PerformedMove, 60> performedMoves;

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
        bool IsMoveValid(Position &moveStartPos, Direction moveDir, std::vector<Field> &fieldsInMoveDirection) const;

        std::vector<Move> GetPossibleMoves() const;
        void PerformMove(Move &move);
        void RevertLastPerformedMove();

        bool IsCapture(const Position &moveDestinationPos) const;

        Move GetLastPerformedMove();

        bool IsGameOver() const;
        GameResult GetGameResult() const;
    };
} // namespace Piranhas