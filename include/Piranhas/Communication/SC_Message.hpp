#pragma once

#include <string>

#include "SC_MessageType.hpp"

namespace Piranhas::Communication {
    struct SC_Message {
        std::string content;
        SC_MessageType messageType;

        SC_Message(std::string messageString, SC_MessageType messageType);
    };
}
