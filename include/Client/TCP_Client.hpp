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

        const std::string delimiter = "\r\n\r\n";

        public:
        TCP_Client();

        void ConnectWithIP(std::string address, unsigned short port);
        void ConnectWithHostname(std::string address, unsigned short port);

        void SendMessage(std::string message);

        std::string ReadMessage();
    };
} // namespace TCP_Client