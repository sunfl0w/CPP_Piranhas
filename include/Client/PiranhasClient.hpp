#pragma once

#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <boost/asio.hpp>

#include "Client/TCP_Client.hpp"
#include "Piranhas/Communication/SC_MessageHandler.hpp"
#include "Piranhas/Communication/SC_Message.hpp"
#include "Piranhas/Communication/SC_MessageType.hpp"
#include "Piranhas/PlayerColor.hpp"
#include "Piranhas/Move.hpp"
#include "Piranhas/GameState.hpp"
#include "AI/Logic/PiranhasLogic.hpp"
#include "AI/Logic/Piranhas_MCTS_Logic.hpp"
#include "AI/Logic/Piranhas_Negamax_Logic.hpp"

namespace Client {
    class PiranhasClient {
        Client::TCP_Client tcpClient;
        Piranhas::Communication::SC_MessageHandler scMessageHandler;

        std::string roomID;
        Piranhas::PlayerColor ownPlayerColor;
        Piranhas::GameState currentGameState;
        bool gameOver = false;

        AI::Logic::PiranhasLogic *logic = new AI::Logic::Piranhas_Negamax_Logic(1700);


        void ClientLoop();
        void Shutdown();

        std::vector<Piranhas::Communication::SC_Message> HandleIncomingMessagesAndGenerateRespones(std::vector<Piranhas::Communication::SC_Message> incomingMessages);

        Piranhas::Move GetNextMove();

    public:
        PiranhasClient(io_service &ioService);
        void Start(ip::address, unsigned short port);
        void StartReserved(std::string hostanme, unsigned short port, std::string reservationCode);
    };
} // namespace Piranhas::Client