#pragma once

#include "nyan/telnet/events.h"

#include <span>
#include <vector>

namespace nyan::telnet {
class Parser {
public:
    std::vector<Event> feed(std::span<const Byte> bytes);
    // Called at EOF. A truncated command/subnegotiation is an error.
    void finish();

private:
    // TODO: Choose persistent parsing state. TCP reads are not messages.
};
} // namespace nyan::telnet
