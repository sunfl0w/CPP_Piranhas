#pragma once

#include <iostream>
#include <pugixml.hpp>
#include <string>
#include <vector>
#include <algorithm>

#include "Piranhas/GameState.hpp"
#include "Piranhas/Move.hpp"
#include "Piranhas/PlayerColor.hpp"
#include "Piranhas/Communication/SC_Message.hpp"
#include "PugiXmlAdditions/XmlStringWriter.hpp"

namespace Piranhas::Communication {
    class SC_MessageHandler {
    private:
        std::vector<SC_Message> FilterProtocolMessages(std::string &inputStream);
    public:
        SC_MessageHandler();

        std::vector<SC_Message> SplitInputMessagesIntoValidSC_Messages(std::string inputStream);

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