#pragma once

#include <string>
#include <iostream>
#include <chrono>
#include <thread>

#include "TCP_Client.hpp"

using namespace Networking_Client;

namespace Piranhas::Client {
    class PiranhasClient {
        TCP_Client tcpClient;

    public:
        PiranhasClient();
        void Start(std::string address, unsigned short port);
    };
} // namespace Piranhas::Client