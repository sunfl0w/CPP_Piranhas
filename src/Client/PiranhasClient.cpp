#include "PiranhasClient.hpp"

using namespace Piranhas::Client;
using namespace Piranhas;

PiranhasClient::PiranhasClient(io_service &ioService) : tcpClient(ioService) {}

void PiranhasClient::ClientLoop() {
    while (!gameOver) {
        //std::cout << "Listening" << "\n";
        std::string inputStream = tcpClient.ReadMessage();
        std::vector<SC_Message> messages = scMessageHandler.SplitInputMessagesIntoValidSC_Messages(inputStream);
        for (SC_Message message : messages) {
            //std::cout << message.content << "\n";
            std::cerr << message.content << "\n";
        }
        std::vector<SC_Message> responses = HandleIncomingMessagesAndGenerateRespones(messages);
        for (SC_Message response : responses) {
            //std::cout << response.content << "\n";
            std::cerr << response.content << "\n";
            tcpClient.SendMessage(response.content);
        }
        //std::cout << "Message: " << tcpClient.ReadMessage() << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void PiranhasClient::Shutdown() {
    tcpClient.SendMessage(scMessageHandler.CreateProtocolEndMessage().content);
}

std::vector<SC_Message> PiranhasClient::HandleIncomingMessagesAndGenerateRespones(std::vector<SC_Message> incomingMessages) {
    std::vector<SC_Message> responseMessages;
    for (SC_Message message : incomingMessages) {
        if (message.messageType == SC_MessageType::Joined) {
            std::string roomId = scMessageHandler.GetRoomIDFromJoinedMessage(message);
            roomID = roomId;
        } else if (message.messageType == SC_MessageType::Welcome) {
            ownPlayerColor = scMessageHandler.GetPlayerColorFromWelcomeMessage(message);
        } else if (message.messageType == SC_MessageType::GameState) {
            GameState gameState = scMessageHandler.GetGameStateFromGameStateMessage(message);
            currentGameState = gameState;
        } else if (message.messageType == SC_MessageType::MoveRequest) {
            if (!gameOver) {
                Move nextMove = GetNextMove();
                if (!currentGameState.IsMoveValid(nextMove)) {
                    currentGameState.board.Print();
                    std::string direction = "??";
                    switch (nextMove.GetDirection()) {
                    case Direction::Up_Right:
                        direction = "Up_Right";
                        break;
                    case Direction::Up:
                        direction = "Up";
                        break;
                    case Direction::Down_Right:
                        direction = "Down_Right";
                        break;
                    case Direction::Right:
                        direction = "Right";
                        break;
                    case Direction::Down_Left:
                        direction = "Down_Left";
                        break;
                    case Direction::Down:
                        direction = "Down";
                        break;
                    case Direction::Up_Left:
                        direction = "Up_Left";
                        break;
                    case Direction::Left:
                        direction = "Left";
                        break;
                    }

                    std::cout << "Move: " << nextMove.GetStartPosition().x << "|" << nextMove.GetStartPosition().y << "|" << direction << "\n";
                }
                responseMessages.push_back(scMessageHandler.CreateMoveMessage(nextMove, roomID));
            }
        } else if (message.messageType == SC_MessageType::Left) {
            //gameOver = true;
        } else if (message.messageType == SC_MessageType::Result) {
            gameOver = true;
        } else if (message.messageType == SC_MessageType::Error) {
            gameOver = true;
        } else if (message.messageType == SC_MessageType::ProtocolEnd) {
            gameOver = true;
        }
    }
    return responseMessages;
}

Move PiranhasClient::GetNextMove() {
    //std::vector<Move> possibleMoves = currentGameState.GetPossibleMoves();
    //return possibleMoves[0];
    return logic->GetNextMove(currentGameState, ownPlayerColor);
}

void PiranhasClient::Start(ip::address address, unsigned short port) {
    tcpClient.ConnectWithIP(address, port);
    tcpClient.SendMessage("<protocol>");
    tcpClient.SendMessage(scMessageHandler.CreateJoinRequestMessage().content);
    ClientLoop();
    Shutdown();
    std::cout << "Disconnect complete. Bye."
              << "\n";
}

void PiranhasClient::StartReserved(std::string hostname, unsigned short port, std::string reservationCode) {
    if (hostname == "localhost") {
        tcpClient.ConnectWithIP(ip::address::from_string("127.0.0.1"), port);
        //tcpClient.ConnectWithIP(tcpClient.ResolveHostnameToIP(hostname), port);
    } else {
        tcpClient.ConnectWithIP(tcpClient.ResolveHostnameToIP(hostname), port);
    }
    tcpClient.SendMessage("<protocol>");
    tcpClient.SendMessage(scMessageHandler.CreateJoinReservedRequestMessage(reservationCode).content);
    ClientLoop();
    Shutdown();
    std::cout << "Disconnect complete. Bye."
              << "\n";
}