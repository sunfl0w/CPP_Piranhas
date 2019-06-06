#include "Client/TCP_Client.hpp"

using namespace Client;

TCP_Client::TCP_Client(io_service &ioService) : ioService(ioService), socket(ioService) {}

void TCP_Client::ConnectWithIP(ip::address address, unsigned short port) {
    socket.connect(tcp::endpoint(address, port));
}

ip::address TCP_Client::ResolveHostnameToIP(std::string hostname) {
    boost::asio::ip::tcp::resolver resolver(ioService);
    boost::asio::ip::tcp::resolver::query query(hostname, "");
    boost::asio::ip::tcp::resolver::iterator i = resolver.resolve(query);
    boost::asio::ip::tcp::endpoint endpoint = *i;
    return endpoint.address();
}

void TCP_Client::Disconnect() {
    socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    socket.close();
}

void TCP_Client::SendMessage(std::string message) {
    boost::system::error_code errorCode;
    write(socket, buffer(message), errorCode);
    if (errorCode) {
        std::cout << "Sending failed: " << errorCode.message() << "\n";
    }
}

std::string TCP_Client::ReadMessage(boost::system::error_code &errorCode) {
    streambuf receiveBuffer;
    read_until(socket, receiveBuffer, "</room>", errorCode);
    //read(socket, receiveBuffer, transfer_at_least(1000), errorCode);
    if (errorCode) {
        std::cout << "Receiving failed: " << errorCode.message() << "\n";
        return "";
    } else {
        const char *message = buffer_cast<const char *>(receiveBuffer.data());
        return std::string(message);
    }
}