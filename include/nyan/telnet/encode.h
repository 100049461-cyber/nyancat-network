#pragma once

#include "nyan/bytes.h"

#include <span>

namespace nyan::telnet {
Bytes encode_command(Byte command, Byte option);
Bytes encode_subnegotiation(Byte option, std::span<const Byte> payload);
} // namespace nyan::telnet
