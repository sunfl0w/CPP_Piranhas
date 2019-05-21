#include "TCP_Client.hpp"

using namespace Networking_Client;

TCP_Client::TCP_Client() : socket(ioService) {}

void TCP_Client::ConnectWithIP(std::string address, unsigned short port) {
    socket.connect(tcp::endpoint(ip::address::from_string(address), port));
}

void TCP_Client::ConnectWithHostname(std::string hostName, unsigned short port) {
    tcp::resolver resolver(ioService);
    tcp::resolver::query query(hostName, "");
    tcp::resolver::iterator iterator = resolver.resolve(query);
    boost::asio::ip::tcp::endpoint endpoint = *iterator;
    socket.connect(endpoint);
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
    read_until(socket, receiveBuffer, "</room>", errorCode);
    //read(socket, receiveBuffer, transfer_at_least(1000), errorCode);
    if (errorCode) {
        std::cout << "Receiving failed: " << errorCode.message() << "\n";
        return "";
    } else {
        const char* message = buffer_cast<const char*>(receiveBuffer.data());
        return std::string(message);
    }
}