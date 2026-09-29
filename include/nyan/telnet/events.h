#pragma once

#include "nyan/bytes.h"

namespace nyan::telnet {
struct Event {
    enum class Kind { data, negotiation, subnegotiation };
    Kind kind;
    Byte command = 0; // WILL/WONT/DO/DONT for negotiation events.
    Byte option = 0;  // Used by negotiation and subnegotiation events.
    Bytes payload;    // Data bytes or unescaped subnegotiation body (no option byte).
};
}
