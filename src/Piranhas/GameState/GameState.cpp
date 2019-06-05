#include <iostream>
#include <vector>

#include "GameState.hpp"
#include "Move.hpp"
#include "Player.hpp"
#include "PlayerColor.hpp"

using namespace Piranhas;

GameState::GameState() {
    board = Board();
    turnCount = 0;
}

GameState::GameState(PlayerColor startingPlayerColor) {
    board = Board();
    board.Populate();
    turnCount = 0;
    currentPlayer = Player(startingPlayerColor);
}

GameState::GameState(GameState &gameState) {
    board = Board(gameState.board);
    turnCount = gameState.turnCount;
    currentPlayer = Player(gameState.currentPlayer);
    //if (&gameState.lastPerformedMove != NULL) {
        lastPerformedMove = Move(gameState.lastPerformedMove);
        lastPerformedMoveDestinationPos = Position(gameState.lastPerformedMoveDestinationPos);
    //}
}

GameState::GameState(const GameState &gameState) {
    board = Board(gameState.board);
    turnCount = gameState.turnCount;
    currentPlayer = Player(gameState.currentPlayer);
    //if (&gameState.lastPerformedMove != NULL) {
        lastPerformedMove = Move(gameState.lastPerformedMove);
        lastPerformedMoveDestinationPos = Position(gameState.lastPerformedMoveDestinationPos);
    //}
}

void GameState::SwapPlayers() {
    if (currentPlayer.color == PlayerColor::Red) {
        currentPlayer = Player(PlayerColor::Blue);
    } else {
        currentPlayer = Player(PlayerColor::Red);
    }
}

Player GameState::GetCurrentPlayer() const {
    return currentPlayer;
}

Player GameState::GetOtherPlayer() const {
    return currentPlayer.GetOppositePlayer();
}

bool GameState::IsMoveValid(Move &move) const {
    if (!board.IsPositionOnBoard(move.GetStartPosition())) {
        //std::cout << "StartNotOnBoard" << "\n";
        return false;
    }
    if (board.GetField(move.GetStartPosition()).fieldType != currentPlayer.fieldType) {
        //std::cout << "NotOfOwnPlayer" << "\n";
        return false;
    }
    int moveDistance = board.GetMoveDistance(move);
    Position destinationPos = board.GetDestinationPositionOfMove(move, moveDistance);
    if (!board.IsPositionOnBoard(destinationPos)) {
        //std::cout << "DestNotOnBoard" << "\n";
        return false;
    }
    FieldType otherPlayerFieldType = GetOtherPlayer().fieldType;
    if (board.IsMovePathBlocked(move, otherPlayerFieldType)) {
        //std::cout << "Blocked" << "\n";
        return false;
    }
    if (board.GetField(destinationPos).fieldType == otherPlayerFieldType || board.GetField(destinationPos).fieldType == FieldType::Empty) {
        return true;
    } else {
        //std::cout << "DestBlocked" << "\n";
        return false;
    }
}

bool GameState::IsMoveValid(Move &move, std::vector<Field> &fieldsInMoveDirection) const {
    if (!board.IsPositionOnBoard(move.GetStartPosition())) {
        return false;
    }
    if (board.GetField(move.GetStartPosition()).fieldType != currentPlayer.fieldType) {
        return false;
    }
    int moveDistance = board.GetCheckerCountInDirection(fieldsInMoveDirection);
    Position destinationPos = board.GetDestinationPositionOfMove(move, moveDistance);
    if (!board.IsPositionOnBoard(destinationPos)) {
        return false;
    }
    FieldType otherPlayerFieldType = GetOtherPlayer().fieldType;
    if (board.IsMovePathBlocked(move, otherPlayerFieldType, fieldsInMoveDirection)) {
        return false;
    }
    if (board.GetField(destinationPos).fieldType == otherPlayerFieldType || board.GetField(destinationPos).fieldType == FieldType::Empty) {
        return true;
    } else {
        return false;
    }
}

std::vector<Move> GameState::GetPossibleMoves() const {
    const std::vector<Direction> directions{Direction::Up, Direction::Up_Right, Direction::Right, Direction::Down_Right, Direction::Down, Direction::Down_Left, Direction::Left, Direction::Up_Left};
    std::vector<Move> possibleMoves;
    std::vector<Field> occupiedFields = board.GetAllFieldsOfSameType(currentPlayer.fieldType);
    for (Field field : occupiedFields) {
        for (Direction dir : directions) {
            std::vector<Field> fieldsInMoveDirection = board.GetFieldsInDirection(field.position, dir);
            int moveDistance = board.GetCheckerCountInDirection(fieldsInMoveDirection);
            Move possibleMove = Move(field.position, dir);
            if (IsMoveValid(possibleMove, fieldsInMoveDirection)) {
                possibleMoves.push_back(possibleMove);
            }
        }
    }
    return possibleMoves;
}

void GameState::PerformMove(Move &move) {
    if (IsGameOver()) {
        std::cout << "Game is over. Move will not be performed." << "\n";
    }
    if (IsMoveValid(move)) {
        Position destinationPos = board.GetDestinationPositionOfMove(move);
        Position startPos = move.GetStartPosition();
        board.SetFieldType(startPos, FieldType::Empty);
        board.SetFieldType(destinationPos, currentPlayer.fieldType);
        lastPerformedMoveDestinationPos = Position(destinationPos);

        turnCount++;
        SwapPlayers();
        lastPerformedMove = Move(move);
        //std::cout << "";

    } else {
        std::cout << "Move is invalid. Move will not be performed." << "\n";
    }
}

void GameState::RevertLastPerformedMove() {
    
}

bool GameState::IsGameOver() const {
    if (turnCount >= 60) {
        return true;
    } else if (currentPlayer.color == PlayerColor::Red && board.IsSwarmComplete(PlayerColor::Red)) {
        return true;
    } else if (board.IsSwarmComplete(PlayerColor::Blue)) {
        return true;
    } else {
        return false;
    }
}

GameResult GameState::GetGameResult() const {
    int swarmSizeRed = board.GetBiggestSwarmSize(PlayerColor::Red);
    int swarmSizeBlue = board.GetBiggestSwarmSize(PlayerColor::Blue);

    bool isRedSwarmComplete = board.IsSwarmComplete(Player(PlayerColor::Red), swarmSizeRed);
    bool isBlueSwarmComplete = board.IsSwarmComplete(Player(PlayerColor::Blue), swarmSizeBlue);
    if (turnCount >= 60) {
        if (swarmSizeRed > swarmSizeBlue) {
            return GameResult::RedWin;
        } else if (swarmSizeRed < swarmSizeBlue) {
            return GameResult::BlueWin;
        }
    } else if (isRedSwarmComplete) {
        return GameResult::RedWin;
    } else if (isBlueSwarmComplete) {
        return GameResult::BlueWin;
    } else {
        return GameResult::Draw;
    }
    //board.Print();
    //std::cout << "Victorious player could not be identified." << "\n";
}