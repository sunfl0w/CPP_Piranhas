#include "TCP_Client.hpp"

using namespace Networking_Client;

TCP_Client::TCP_Client() : socket(ioService) {}

void TCP_Client::Connect(std::string address, unsigned short port) {
    socket.connect(tcp::endpoint(ip::address::from_string(address), port));
}

void TCP_Client::SendMessage(std::string message) {
    boost::system::error_code errorCode;
    write(socket, buffer(message), errorCode);
    if (errorCode) {
        std::cout << "Sending failed: " << errorCode.message() << "\n";
    }
}

std::string TCP_Client::ReadMessage() {
    boost::system::error_code errorCode;
    streambuf receiveBuffer;
    read(socket, receiveBuffer, transfer_at_least(1000), errorCode);
    if (errorCode) {
        std::cout << "Receiving failed: " << errorCode.message() << "\n";
        return "";
    } else {
        const char* message = buffer_cast<const char*>(receiveBuffer.data());
        return std::string(message);
    }
}