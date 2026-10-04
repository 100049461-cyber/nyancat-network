#include "nyan/terminal.h"

#include <cerrno>
#include <cstdio>
#include <system_error>

#include <sys/ioctl.h>
#include <unistd.h>

namespace nyan {
WindowSize terminal_size() {
    struct winsize size{};

    if (::ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) == 0 &&
        size.ws_col != 0 && size.ws_row != 0) {
        return WindowSize{size.ws_col, size.ws_row};
    }

    return WindowSize{80, 24};
}

void write_terminal(std::span<const Byte> bytes) {
    std::size_t pos = 0;

    while (pos < bytes.size()) {
        ssize_t written =
            ::write(STDOUT_FILENO, bytes.data() + pos,
                    bytes.size() - pos);

        if (written > 0) {
            pos += static_cast<std::size_t>(written);
            continue;
        }

        if (written == -1 && errno == EINTR) {
            continue;
        }

        if (written == 0) {
            throw std::system_error(
                std::make_error_code(std::errc::io_error),
                "write");
        }

        throw std::system_error(
            errno,
            std::generic_category(),
            "write");
    }
}

void restore_terminal() noexcept {
    if (::isatty(STDOUT_FILENO) != 1) {
        return;
    }

    static constexpr Byte cleanup[] = {
        0x1b, '[', '0', 'm',
        0x1b, '[', '?', '2', '5', 'h'
    };

    try {
        write_terminal(cleanup);
    } catch (...) {
    }
}
}