#include "PiranhasClient.hpp"

using namespace Piranhas::Client;

PiranhasClient::PiranhasClient() {}

void PiranhasClient::Start(std::string address, unsigned short port) {
    tcpClient.Connect(address, port);
    tcpClient.SendMessage("<protocol>");
    tcpClient.SendMessage("<join gameType=\"swc_2019_piranhas\"/>");


    while(true) {
        std::cout << "Listening" << "\n";
        std::string inputStream = tcpClient.ReadMessage();
        std::vector<SC_Message> messages = scMessageHandler.SplitInputMessagesIntoValidSC_Messages(inputStream);
        //std::cout << "Message: " << tcpClient.ReadMessage() << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}