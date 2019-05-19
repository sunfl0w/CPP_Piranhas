#include "SC_MessageHandler.hpp"

using namespace Piranhas::Communication;

SC_MessageHandler::SC_MessageHandler() {}

std::vector<SC_Message> SC_MessageHandler::SplitInputMessagesIntoValidXMLMessages(std::string inputStream) {
    std::vector<SC_Message> messages;

    //Removing non xml-compliant messages. Duhhh!
    std::size_t protocolPos = inputStream.find("<protocol>");
    if(protocolPos != std::string::npos) {
        std::string protocolMessage = inputStream.substr(protocolPos, 10);
        inputStream.erase(protocolPos, 10);
        messages.push_back(SC_Message(protocolMessage, SC_MessageType::Protocol));
    }

    std::size_t protocolEndPos = inputStream.find("</protocol>");
    if(protocolEndPos != std::string::npos) {
        std::string protocolEndMessage = inputStream.substr(protocolEndPos, 11);
        inputStream.erase(protocolPos, 11);
        messages.push_back(SC_Message(protocolEndMessage, SC_MessageType::ProtocolEnd));
    }

    //Wrapping xml-compliant messages for easy parsing
    inputStream.insert(0, "<SC_Message>");
    inputStream.append("</SC_Message>");

    pugi::xml_document scMessageDoc;
    scMessageDoc.load_string(inputStream.data());
    for(pugi::xml_node node : scMessageDoc.children()) {
        for(pugi::xml_node node2 : node.children())
        std::cout << node2.name() << "\n";
    }

    return messages;
}