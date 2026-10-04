#pragma once

#include <span>
#include <string>
#include <string_view>

namespace nyan {
struct Options {
    std::string host = "127.0.0.1";
    std::string port = "2323";
    bool help = false;
};

// args excludes argv[0]. Invalid input throws std::invalid_argument.
Options parse_options(std::span<const std::string_view> args);
std::string_view usage();
} // namespace nyan
