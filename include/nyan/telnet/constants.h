#pragma once

#include "nyan/bytes.h"

namespace nyan::telnet {
// Telnet command codes: RFC 854, "TELNET COMMAND STRUCTURE".
inline constexpr Byte kIac = 255;
inline constexpr Byte kDont = 254;
inline constexpr Byte kDo = 253;
inline constexpr Byte kWont = 252;
inline constexpr Byte kWill = 251;
inline constexpr Byte kSb = 250;
inline constexpr Byte kSe = 240;
inline constexpr Byte kNop = 241;

// Option codes: https://www.iana.org/assignments/telnet-options/
inline constexpr Byte kEcho = 1;
inline constexpr Byte kSuppressGoAhead = 3;
inline constexpr Byte kTerminalType = 24;
inline constexpr Byte kWindowSize = 31;
inline constexpr Byte kLineMode = 34;
inline constexpr Byte kNewEnvironment = 39;

// Terminal-type subcommands: RFC 1091, section 2.
inline constexpr Byte kIs = 0;
inline constexpr Byte kSend = 1;
} // namespace nyan::telnet
