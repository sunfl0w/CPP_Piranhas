#include "Piranhas/GameState.hpp"

#include <iostream>
#include <vector>

#include "Piranhas/Move.hpp"
#include "Piranhas/Player.hpp"
#include "Piranhas/PlayerColor.hpp"

using namespace Piranhas;
using namespace Piranhas::Constants;

GameState::GameState() {
    board = Board();
    moveDistanceBoard = MoveDistanceBoard();
    turnCount = 0;
}

GameState::GameState(PlayerColor startingPlayerColor) {
    board = Board();
    moveDistanceBoard = MoveDistanceBoard();
    board.Populate();
    turnCount = 0;
    currentPlayer = Player(startingPlayerColor);
}

GameState::GameState(GameState &gameState) {
    board = Board(gameState.board);
    moveDistanceBoard = MoveDistanceBoard(gameState.moveDistanceBoard);
    turnCount = gameState.turnCount;
    currentPlayer = Player(gameState.currentPlayer);
    performedMoves = std::array<PerformedMove, 60>(gameState.performedMoves);
}

GameState::GameState(const GameState &gameState) {
    board = Board(gameState.board);
    moveDistanceBoard = MoveDistanceBoard(gameState.moveDistanceBoard);
    turnCount = gameState.turnCount;
    currentPlayer = Player(gameState.currentPlayer);
    performedMoves = std::array<PerformedMove, 60>(gameState.performedMoves);
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
    int moveDistance = moveDistanceBoard.GetMoveDistance(move);//board.GetMoveDistance(move);
    Position destinationPos = board.GetDestinationPositionOfMove(move, moveDistance);
    if (!board.IsPositionOnBoard(destinationPos)) {
        //std::cout << "DestNotOnBoard" << "\n";
        return false;
    }
    FieldType otherPlayerFieldType = GetOtherPlayer().fieldType;
    /*if (board.IsMovePathBlocked(move, otherPlayerFieldType)) {
        //std::cout << "Blocked" << "\n";
        return false;
    }
    if (board.GetField(destinationPos).fieldType == otherPlayerFieldType || board.GetField(destinationPos).fieldType == FieldType::Empty) {
        return true;
    } else {
        //std::cout << "DestBlocked" << "\n";
        return false;
    }*/
    if(board.IsMovePathBlocked(move, moveDistance, otherPlayerFieldType)) {
        return false;
    }
    return true;
}

bool GameState::IsMoveValid(Move &move, std::vector<Field> &fieldsInMoveDirection) const {
    if (!board.IsPositionOnBoard(move.GetStartPosition())) {
        return false;
    }
    if (board.GetField(move.GetStartPosition()).fieldType != currentPlayer.fieldType) {
        return false;
    }
    int moveDistance = moveDistanceBoard.GetMoveDistance(move);//board.GetCheckerCountInDirection(fieldsInMoveDirection);
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
    return true;
}

bool GameState::IsMoveValid(Position &moveStartPos, Direction moveDir, std::vector<Field> &fieldsInMoveDirection) const {
    if (!board.IsPositionOnBoard(moveStartPos)) {
        return false;
    }
    if (board.GetField(moveStartPos).fieldType != currentPlayer.fieldType) {
        return false;
    }
    int moveDistance = moveDistanceBoard.GetMoveDistance(Move(moveStartPos, moveDir));//board.GetCheckerCountInDirection(fieldsInMoveDirection);
    Position destinationPos = board.GetDestinationPositionOfMove(moveStartPos, moveDir, moveDistance);
    if (!board.IsPositionOnBoard(destinationPos)) {
        return false;
    }
    FieldType otherPlayerFieldType = GetOtherPlayer().fieldType;
    if (board.IsMovePathBlocked(moveStartPos, moveDir, otherPlayerFieldType, fieldsInMoveDirection)) {
        return false;
    }
    if (board.GetField(destinationPos).fieldType == otherPlayerFieldType || board.GetField(destinationPos).fieldType == FieldType::Empty) {
        return true;
    } else {
        return false;
    }
}

std::vector<Move> GameState::GetPossibleMoves() const {
    std::vector<Move> possibleMoves;
    //std::vector<Field> occupiedFields = board.GetAllFieldsOfSameType(currentPlayer.fieldType);
    //for (Field field : occupiedFields) {
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            Field field = board.GetField(x, y);
            if (field.fieldType == currentPlayer.fieldType) {
                for (Direction dir : directions) {
                    //std::vector<Field> fieldsInMoveDirection = board.GetFieldsInDirection(field.position, dir);
                    //int moveDistance = board.GetCheckerCountInDirection(fieldsInMoveDirection);
                    Move possibleMove = Move(field.position, dir);
                    if (IsMoveValid(possibleMove)) {
                        possibleMoves.push_back(possibleMove);
                    }
                    /*if (IsMoveValid(field.position, dir, fieldsInMoveDirection)) {
                        possibleMoves.push_back(Move(field.position, dir));
                    }*/
                }
            }
        }
    }
    return possibleMoves;
}

void GameState::PerformMove(Move &move) {
    /*if (IsGameOver()) {
        std::cout << "Game is over. Move will not be performed."
                  << "\n";
    }*/
    if (IsMoveValid(move)) {
        Position destinationPos = board.GetDestinationPositionOfMove(move);
        Position startPos = move.GetStartPosition();
        bool isMoveCaptue = IsCapture(destinationPos);
        performedMoves[turnCount] = PerformedMove(move, destinationPos, board.GetField(destinationPos).fieldType, isMoveCaptue);
        board.SetFieldTypeAtPosition(startPos, FieldType::Empty);
        board.SetFieldTypeAtPosition(destinationPos, currentPlayer.fieldType);

        moveDistanceBoard.PerformMove(startPos, destinationPos, isMoveCaptue);

        turnCount++;
        SwapPlayers();
        
        //std::cout << "";

    } else {
        std::cout << "Move is invalid, it will not be performed."
                  << "\n";
    }
}

void GameState::RevertLastPerformedMove() {
    PerformedMove performedMove = performedMoves[turnCount - 1];
    board.SetFieldTypeAtPosition(performedMove.move.GetStartPosition(), currentPlayer.GetOppositePlayer().fieldType);
    board.SetFieldTypeAtPosition(performedMove.destinationPos, performedMove.formerDestinationFieldType);

    moveDistanceBoard.RevertMove(performedMove);

    turnCount--;
    SwapPlayers();
}

bool GameState::IsCapture(const Position &moveDestinationPos) const {
    if(board.GetField(moveDestinationPos).fieldType == currentPlayer.GetOppositePlayer().fieldType) {
        return true;
    } else {
        return false;
    }
}

bool GameState::IsGameOver() const {
    if(turnCount % 2 == 1) {
        return false;
    }
    if (turnCount >= 60) {
        //std::cout << "Turn limit." << "”\n";
        return true;
    } 
    
    if(board.IsSwarmComplete(PlayerColor::Red) || board.IsSwarmComplete(PlayerColor::Blue)) {
        return true;
    }
        
    return false;   
}

Move GameState::GetLastPerformedMove() {
    return performedMoves[turnCount - 1].move;
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