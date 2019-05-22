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

        void ConnectWithIP(ip::address address, unsigned short port);
        ip::address ResolveHostnameToIP(std::string hostname);

        void SendMessage(std::string message);

        std::string ReadMessage();
    };
} // namespace TCP_Client