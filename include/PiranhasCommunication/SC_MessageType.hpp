#pragma once

namespace Piranhas::Communication {
    enum class SC_MessageType
    {
        Protocol,
        ProtocolEnd,
        Welcome,
        JoinRequest,
        JoinRequestPrepared,
        Joined,
        GameState,
        Move,
        MoveRequest,
        Result,
    };
}