#pragma once

#include "nyan/bytes.h"

namespace nyan::telnet {
inline constexpr Byte kIac = 255, kDont = 254, kDo = 253, kWont = 252, kWill = 251, kSb = 250, kSe = 240, kNopn = 241, kEcho = 1, kSuppressGoAhead = 3, kTerminalType = 24, kWindowSize = 31, kLineMode = 34, kNewEnvironment = 39, kIs = 0, kSend = 1
}
