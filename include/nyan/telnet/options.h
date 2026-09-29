#pragma once

#include "nyan/bytes.h"
#include "nyan/terminal.h"

namespace nyan::telnet {
Bytes terminal_type_reply(); // Codespaces: xterm-256color.
Bytes window_size_reply(WindowSize size);
}
