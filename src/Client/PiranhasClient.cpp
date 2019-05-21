#include "PiranhasClient.hpp"

using namespace Piranhas::Client;
using namespace Piranhas;

PiranhasClient::PiranhasClient() {}

void PiranhasClient::ClientLoop() {
    while(!gameOver) {
        std::cout << "Listening" << "\n";
        std::string inputStream = tcpClient.ReadMessage();
        std::vector<SC_Message> messages = scMessageHandler.SplitInputMessagesIntoValidSC_Messages(inputStream);
        for(SC_Message message : messages) {
            std::cout << message.content << "\n";
        }
        std::vector<SC_Message> responses = HandleIncomingMessagesAndGenerateRespones(messages);
        for(SC_Message response : responses) {
            std::cout << response.content << "\n";
            tcpClient.SendMessage(response.content);
        }
        //std::cout << "Message: " << tcpClient.ReadMessage() << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

std::vector<SC_Message> PiranhasClient::HandleIncomingMessagesAndGenerateRespones(std::vector<SC_Message> incomingMessages) {
    std::vector<SC_Message> responseMessages;
    for(SC_Message message : incomingMessages) {
        if(message.messageType == SC_MessageType::Joined) {
            std::string roomId = scMessageHandler.GetRoomIDFromJoinedMessage(message);
            roomID = roomId;
        } else if(message.messageType == SC_MessageType::Welcome) {
            ownPlayerColor = scMessageHandler.GetPlayerColorFromWelcomeMessage(message);
        } else if(message.messageType == SC_MessageType::GameState) {
            GameState gameState = scMessageHandler.GetGameStateFromGameStateMessage(message);
            currentGameState = gameState;
        } else if(message.messageType == SC_MessageType::MoveRequest) {
            responseMessages.push_back(scMessageHandler.CreateMoveMessage(GetNextMove(), roomID));
        } else if(message.messageType == SC_MessageType::Result) {
            gameOver = true;
        }
    }
    return responseMessages;
}

Move PiranhasClient::GetNextMove() {
    std::vector<Move> possibleMoves = currentGameState.GetPossibleMoves();
    return possibleMoves[0];
}

void PiranhasClient::Start(std::string address, unsigned short port) {
    tcpClient.ConnectWithIP(address, port);
    tcpClient.SendMessage("<protocol>");
    tcpClient.SendMessage("<join gameType=\"swc_2019_piranhas\"/>");
    ClientLoop();
}

void PiranhasClient::StartReserved(std::string address, unsigned short port, std::string reservationCode) {
    tcpClient.ConnectWithIP(address, port);
    tcpClient.SendMessage("<protocol>");
    tcpClient.SendMessage(scMessageHandler.CreateJoinReservedRequestMessage(reservationCode).content);
    ClientLoop();
}