#include "SC_Message.hpp"

using namespace Piranhas::Communication;

SC_Message::SC_Message(std::string messageString, SC_MessageType messageType) {
    this->content = messageString;
    this->messageType = messageType;
}