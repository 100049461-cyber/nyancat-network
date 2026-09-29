#pragma once

#include "nyan/bytes.h"
#include "nyan/socket.h"

#include <cstddef>
#include <span>
#include <string_view>

namespace nyan {
Socket connect_tcp(std::string_view host, std::string_view port);
// An empty buffer is invalid; zero from receive means orderly peer shutdown.
std::size_t receive(int fd, std::span<Byte> buffer);
void send_all(int fd, std::span<const Byte> bytes);
}
