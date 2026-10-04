#pragma once

#include "nyan/telnet/events.h"
#include "nyan/terminal.h"

namespace nyan::telnet {
class Session {
public:
    explicit Session(WindowSize size);
    // Empty means no response; bytes are sent back to the server, not stdout.
    Bytes respond(const Event& event);

private:
    // TODO: Track local and remote option state separately.
};
} // namespace nyan::telnet
