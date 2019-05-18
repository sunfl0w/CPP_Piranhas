#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <string>

using namespace boost::asio;
using boost::asio::ip::tcp;

namespace Networking_Client {
    class TCP_Client {
        io_service ioService;
        tcp::socket socket;

        public:
        TCP_Client();

        void Connect(std::string address, unsigned short port);

        void SendMessage(std::string message);

        std::string ReadMessage();
    };
} // namespace TCP_Client