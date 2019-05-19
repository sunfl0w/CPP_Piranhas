#pragma once

#include <string>
#include <iostream>
#include <chrono>
#include <thread>

#include "TCP_Client.hpp"
#include "SC_MessageHandler.hpp"

using namespace Networking_Client;
using namespace Piranhas::Communication;

namespace Piranhas::Client {
    class PiranhasClient {
        TCP_Client tcpClient;
        SC_MessageHandler scMessageHandler;

    public:
        PiranhasClient();
        void Start(std::string address, unsigned short port);
    };
} // namespace Piranhas::Client