#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <string>

using namespace boost::asio;
using boost::asio::ip::tcp;

namespace Networking_Client {
    class TCP_Client {
        io_service &ioService;
        tcp::socket socket;

        public:
        TCP_Client(io_service &ioService);

        void ConnectWithIP(ip::address address, unsigned short port);

        void Disconnect();

        ip::address ResolveHostnameToIP(std::string hostname);

        void SendMessage(std::string message);

        std::string ReadMessage(boost::system::error_code &errorCode);
    };
} // namespace TCP_Client