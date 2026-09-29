#pragma once

#include "nyan/bytes.h"

#include <cstdint>
#include <span>

namespace nyan {
struct WindowSize {
    std::uint16_t columns;
    std::uint16_t rows;
};

WindowSize terminal_size();
void write_terminal(std::span<const Byte> bytes);
// Best effort, noexcept; only emit cleanup escapes if stdout is a terminal.
void restore_terminal() noexcept;
}
