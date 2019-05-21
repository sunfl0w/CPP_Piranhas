#include "SC_MessageHandler.hpp"

using namespace Piranhas::Communication;

SC_MessageHandler::SC_MessageHandler() {}

std::vector<SC_Message> SC_MessageHandler::FilterProtocolMessages(std::string &inputStream) {
    std::vector<SC_Message> protocolMessages;

    //Removing non xml-compliant messages. Duhhh!
    std::size_t protocolPos = inputStream.find("<protocol>");
    if(protocolPos != std::string::npos) {
        std::string protocolMessage = inputStream.substr(protocolPos, 10);
        inputStream.erase(protocolPos, 10);
        protocolMessages.push_back(SC_Message(protocolMessage, SC_MessageType::Protocol));
    }

    std::size_t protocolEndPos = inputStream.find("</protocol>");
    if(protocolEndPos != std::string::npos) {
        std::string protocolEndMessage = inputStream.substr(protocolEndPos, 11);
        inputStream.erase(protocolEndPos, 11);
        protocolMessages.push_back(SC_Message(protocolEndMessage, SC_MessageType::ProtocolEnd));
    }

    return protocolMessages;
}

std::vector<SC_Message> SC_MessageHandler::SplitInputMessagesIntoValidSC_Messages(std::string inputStream) {
    std::vector<SC_Message> messages;

    std::vector<SC_Message> protocolMessages = FilterProtocolMessages(inputStream);
    messages.insert(std::end(messages), std::begin(protocolMessages), std::end(protocolMessages));

    //Wrapping xml-compliant messages for easy parsing
    inputStream.insert(0, "<SC_Message>");
    inputStream.append("</SC_Message>");

    pugi::xml_document scMessageDoc;
    scMessageDoc.load_string(inputStream.data());
    for(pugi::xml_node scMessageNode : scMessageDoc.children()) {
        for(pugi::xml_node childNode : scMessageNode.children()) {
            SC_MessageType scMessageType;
            /*std::cout << childNode.name() << "\n";
            xmlStringWriter xmlStringWriter;
            childNode.print(xmlStringWriter, " ", pugi::format_default);
            std::cout << xmlStringWriter.stringData << "\n";*/
            std::string childNodeName(childNode.name());

            //childNodeName.erase(childNodeName.find_last_not_of("\n\r") + 1);
            //childNodeName.erase(std::remove(childNodeName.begin(), childNodeName.end(), ' '), childNodeName.end());

            if(childNodeName == "join") {
                scMessageType = SC_MessageType::JoinRequest;
            } else if(childNodeName == "joinPrepared") {
                scMessageType = SC_MessageType::JoinRequestPrepared;
            } else if(childNodeName == "joined") {
                scMessageType = SC_MessageType::Joined;
            } else if(childNodeName == "room") {
                std::string classAttributeValue = childNode.child("data").attribute("class").value();
                if(classAttributeValue == "welcomeMessage") {
                    scMessageType = SC_MessageType::Welcome;
                } else if(classAttributeValue == "memento") {
                    scMessageType = SC_MessageType::GameState;
                } else if(classAttributeValue == "sc.framework.plugins.protocol.MoveRequest") {
                    scMessageType = SC_MessageType::MoveRequest;
                }
            }
            xmlStringWriter xmlStringWriter;
            childNode.print(xmlStringWriter, " ", pugi::format_default);
            messages.push_back(SC_Message(xmlStringWriter.stringData, scMessageType));
        }
    }

    return messages;
}