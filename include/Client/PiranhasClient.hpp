#pragma once

#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <boost/asio.hpp>

#include "TCP_Client.hpp"
#include "SC_MessageHandler.hpp"
#include "SC_Message.hpp"
#include "SC_MessageType.hpp"
#include "PlayerColor.hpp"
#include "Move.hpp"
#include "GameState.hpp"

using namespace Networking_Client;
using namespace Piranhas::Communication;

namespace Piranhas::Client {
    class PiranhasClient {
        TCP_Client tcpClient;
        SC_MessageHandler scMessageHandler;

        std::string roomID;
        PlayerColor ownPlayerColor;
        GameState currentGameState;
        bool gameOver = false;


        void ClientLoop();

        std::vector<SC_Message> HandleIncomingMessagesAndGenerateRespones(std::vector<SC_Message> incomingMessages);

        Move GetNextMove();

    public:
        PiranhasClient();
        void Start(ip::address, unsigned short port);
        void StartReserved(std::string hostanme, unsigned short port, std::string reservationCode);
    };
} // namespace Piranhas::Client