#pragma once

#include <iostream>
#include <pugixml.hpp>
#include <string>
#include <vector>

#include "GameState.hpp"
#include "Move.hpp"
#include "PlayerColor.hpp"
#include "SC_Message.hpp"

namespace Piranhas::Communication {
    class SC_MessageHandler {
    public:
        SC_MessageHandler();

        std::vector<SC_Message> SplitInputMessagesIntoValidXMLMessages(std::string inputStream);

        std::vector<SC_Message> ClassifyXMLMessages(std::vector<std::string>);

        SC_Message CreateProtocolMessage();
        SC_Message CreateProtocolEndMessage();
        SC_Message CreateJoinRequestMessage();
        SC_Message CreateJoinReservedRequestMessage(std::string reservationCode);
        SC_Message CreateMoveMessage(Move move, std::string roomID);

        PlayerColor GetPlayerColorFromWelcomeMessage(SC_Message message);
        std::string GetRoomIDFromJoinedMessage(SC_Message message);
        GameState GetGameStateFromGameStateMessage(SC_Message message);
    };
} // namespace Piranhas::Communication