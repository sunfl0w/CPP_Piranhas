#pragma once

#include <vector>

#include "PlayerColor.hpp"
#include "Player.hpp"
#include "Move.hpp"
#include "Board.hpp"

namespace Piranhas {
    class GameState {
    public:
        Board board;
        int turnCount;
        Player currentPlayer;
        Player startingPlayer;
        Move lastPerformedMove;

    public:
        GameState();
        GameState(PlayerColor startingPlayerColor);
        GameState(GameState &gameState);
        GameState(const GameState &gameState);

        void SwapPlayers();

        Player GetCurrentPlayer();
        Player GetOtherPlayer();

        bool IsMoveValid(Move &move);
        bool IsMoveValid(Move &move, std::vector<Field> &fieldsInMoveDirection);

        std::vector<Move> GetPossibleMoves();
        void PerformMove(Move &move);

        bool IsGameOver();
        Player GetVictoriousPlayer();
    };
} // namespace Piranhas