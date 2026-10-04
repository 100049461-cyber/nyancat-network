#pragma once

namespace nyan {
class Socket {
public:
    explicit Socket(int fd = -1) noexcept;
    ~Socket();
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;
    Socket(Socket&& other) noexcept;
    Socket& operator=(Socket&& other) noexcept;

    [[nodiscard]] int get() const noexcept;
    [[nodiscard]] int release() noexcept;
    void reset(int fd = -1) noexcept;

private:
    int fd_ = -1;
};
} // namespace nyan
