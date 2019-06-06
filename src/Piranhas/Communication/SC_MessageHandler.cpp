#include "SC_MessageHandler.hpp"

using namespace Piranhas::Communication;
using namespace Piranhas;

SC_MessageHandler::SC_MessageHandler() {}

std::vector<SC_Message> SC_MessageHandler::FilterProtocolMessages(std::string &inputStream) {
    std::vector<SC_Message> protocolMessages;

    //Removing non xml-compliant messages. Duhhh!
    std::size_t protocolPos = inputStream.find("<protocol>");
    if (protocolPos != std::string::npos) {
        std::string protocolMessage = inputStream.substr(protocolPos, 10);
        inputStream.erase(protocolPos, 10);
        protocolMessages.push_back(SC_Message(protocolMessage, SC_MessageType::Protocol));
    }

    std::size_t protocolEndPos = inputStream.find("</protocol>");
    if (protocolEndPos != std::string::npos) {
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
    for (pugi::xml_node scMessageNode : scMessageDoc.children()) {
        for (pugi::xml_node childNode : scMessageNode.children()) {
            SC_MessageType scMessageType;
            /*std::cout << childNode.name() << "\n";
            xmlStringWriter xmlStringWriter;
            childNode.print(xmlStringWriter, " ", pugi::format_default);
            std::cout << xmlStringWriter.stringData << "\n";*/
            std::string childNodeName(childNode.name());

            //childNodeName.erase(childNodeName.find_last_not_of("\n\r") + 1);
            //childNodeName.erase(std::remove(childNodeName.begin(), childNodeName.end(), ' '), childNodeName.end());

            if (childNodeName == "join") {
                scMessageType = SC_MessageType::JoinRequest;
            } else if (childNodeName == "joinPrepared") {
                scMessageType = SC_MessageType::JoinRequestPrepared;
            } else if (childNodeName == "joined") {
                scMessageType = SC_MessageType::Joined;
            } else if (childNodeName == "left") {
                scMessageType = SC_MessageType::Left;
            } else if (childNodeName == "room") {
                std::string classAttributeValue = childNode.child("data").attribute("class").value();
                if (classAttributeValue == "welcomeMessage") {
                    scMessageType = SC_MessageType::Welcome;
                } else if (classAttributeValue == "memento") {
                    scMessageType = SC_MessageType::GameState;
                } else if (classAttributeValue == "sc.framework.plugins.protocol.MoveRequest") {
                    scMessageType = SC_MessageType::MoveRequest;
                } else if (classAttributeValue == "result") {
                    scMessageType = SC_MessageType::Result;
                } else if (classAttributeValue == "MSG") {
                    scMessageType = SC_MessageType::Error;
                }
            }
            xmlStringWriter xmlStringWriter;
            childNode.print(xmlStringWriter, " ", pugi::format_default);
            messages.push_back(SC_Message(xmlStringWriter.stringData, scMessageType));
        }
    }

    return messages;
}

SC_Message SC_MessageHandler::CreateProtocolMessage() {
    return SC_Message("<protocol>", SC_MessageType::Protocol);
}

SC_Message SC_MessageHandler::CreateProtocolEndMessage() {
    return SC_Message("</protocol>", SC_MessageType::ProtocolEnd);
}

SC_Message SC_MessageHandler::CreateJoinRequestMessage() {
    return SC_Message("<join gameType=\"swc_2019_piranhas\" />", SC_MessageType::JoinRequest);
}

SC_Message SC_MessageHandler::CreateJoinReservedRequestMessage(std::string reservationCode) {
    return SC_Message("<joinPrepared reservationCode=\"" + reservationCode + "\" />", SC_MessageType::JoinRequestPrepared);
}

SC_Message SC_MessageHandler::CreateMoveMessage(Move move, std::string roomID) {
    std::string directionString;
    switch (move.GetDirection()) {
    case (Direction::Up):
        directionString = "UP";
        break;
    case (Direction::Down):
        directionString = "DOWN";
        break;
    case (Direction::Left):
        directionString = "LEFT";
        break;
    case (Direction::Right):
        directionString = "RIGHT";
        break;
    case (Direction::Up_Right):
        directionString = "UP_RIGHT";
        break;
    case (Direction::Up_Left):
        directionString = "UP_LEFT";
        break;
    case (Direction::Down_Right):
        directionString = "DOWN_RIGHT";
        break;
    case (Direction::Down_Left):
        directionString = "DOWN_LEFT";
        break;
    }
    return SC_Message("<room roomId=\"" + roomID + "\"><data class=\"move\" x=\"" + std::to_string(move.GetStartPosition().x) + "\" y=\"" + std::to_string(move.GetStartPosition().y) + "\" direction=\"" + directionString + "\" /></room>", SC_MessageType::JoinRequest);
}

PlayerColor SC_MessageHandler::GetPlayerColorFromWelcomeMessage(SC_Message message) {
    pugi::xml_document scMessageDoc;
    scMessageDoc.load_string(message.content.data());
    std::string color(scMessageDoc.child("room").child("data").attribute("color").value());

    if (color == "red") {
        return PlayerColor::Red;
    } else {
        return PlayerColor::Blue;
    }
}
std::string SC_MessageHandler::GetRoomIDFromJoinedMessage(SC_Message message) {
    pugi::xml_document scMessageDoc;
    scMessageDoc.load_string(message.content.data());
    std::string roomID(scMessageDoc.child("joined").attribute("roomId").value());
    return roomID;
}
GameState SC_MessageHandler::GetGameStateFromGameStateMessage(SC_Message message) {
    GameState gameState;
    pugi::xml_document scMessageDoc;
    scMessageDoc.load_string(message.content.data());
    pugi::xml_node roomNode = scMessageDoc.child("room");

    for (pugi::xml_attribute stateAttribute : roomNode.child("data").child("state").attributes()) {
        std::string stateAttributeName(stateAttribute.name());
        if (stateAttributeName == "turn") {
            gameState.turnCount = std::stoi(std::string(stateAttribute.value()));
        } else if (stateAttributeName == "startPlayerColor") {
            std::string playerColor = std::string(stateAttribute.value());
            if (playerColor == "RED") {
                gameState.startingPlayer = Player(PlayerColor::Red);
            } else {
                gameState.startingPlayer = Player(PlayerColor::Blue);
            }
        } else if (stateAttributeName == "currentPlayerColor") {
            std::string playerColor = std::string(stateAttribute.value());
            if (playerColor == "RED") {
                gameState.currentPlayer = Player(PlayerColor::Red);
            } else {
                gameState.currentPlayer = Player(PlayerColor::Blue);
            }
        }
    }

    for (pugi::xml_node fieldsNode : roomNode.child("data").child("state").child("board").children()) {
        for (pugi::xml_node fieldNode : fieldsNode.children()) {
            Position fieldPos;
            FieldType fieldType;
            for (pugi::xml_attribute fieldAttribute : fieldNode.attributes()) {
                std::string fieldAttributeName(fieldAttribute.name());
                if (fieldAttributeName == "x") {
                    std::string x = std::string(fieldAttribute.value());
                    fieldPos.x = std::stoi(x);
                } else if (fieldAttributeName == "y") {
                    std::string y = std::string(fieldAttribute.value());
                    fieldPos.y = std::stoi(y);
                } else if (fieldAttributeName == "state") {
                    std::string fieldAttributeValue(fieldAttribute.value());
                    if (fieldAttributeValue == "RED") {
                        fieldType = FieldType::Red;
                    } else if (fieldAttributeValue == "BLUE") {
                        fieldType = FieldType::Blue;
                    } else if (fieldAttributeValue == "OBSTRUCTED") {
                        fieldType = FieldType::Obstacle;
                    } else if (fieldAttributeValue == "EMPTY") {
                        fieldType = FieldType::Empty;
                    }
                }
            }
            gameState.board.SetFieldTypeAtPosition(fieldPos, fieldType);
        }
    }

    return gameState;
}