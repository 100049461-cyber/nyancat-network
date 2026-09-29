# nyancat-network

A first C++ project for A Programming Club: connect to the original
[klange/nyancat](https://github.com/klange/nyancat) in telnet mode and display its
animation in your terminal. Learn Git, sockets, and how to turn documentation
into working code.

**Status: starter scaffold.** The build, Codespace, and local upstream server are
ready. The client is intentionally unfinished: the
[issues](https://github.com/A-Programming-Club/nyancat-network/issues) are the work.
Running `nyancat-client` currently prints a reminder and exits with status 1.

## Start here

1. Read [CONTRIBUTING.md](CONTRIBUTING.md) for your first branch, commit, and PR.
2. [Fork this repository](https://github.com/A-Programming-Club/nyancat-network/fork).
3. On your fork, choose **Code → Codespaces → Create codespace on main**. Wait for
   the container and first build to finish.
4. Pick an unclaimed task in the [roadmap](docs/roadmap.md). Comment that you want
   it; a club organizer can assign you. Check its prerequisites before coding.

The Codespace includes **GCC 13+ using `-std=gnu++23`, CMake, Ninja, GDB, socat,
telnet, and the original nyancat server**. Use its integrated terminal. Linux is
our supported development platform; Windows and macOS users should use Codespaces.

```bash
cmake --preset dev
cmake --build --preset dev
ctest --preset dev
```

CTest initially reports no tests. Each implementation PR adds useful checks for
its own behavior; see [tests/README.md](tests/README.md).

## See the target behavior

In terminal 1:

```bash
bash scripts/run-server.sh
```

In terminal 2, preview the server with the existing telnet program:

```bash
telnet 127.0.0.1 2323
```

Exit telnet with **Ctrl+]**, type `quit`, then press Enter. If your cursor or colors
look wrong, run `printf '\033[0m\033[?25h\n'`.

Once the client issues are implemented, replace that preview command with:

```bash
./build/nyancat-client 127.0.0.1 2323
```

That client must use C++ sockets directly. Its job is to separate telnet protocol
bytes from animation bytes and write the latter to the terminal. The terminal
already understands ANSI colors and cursor movement.

The server listens only inside your Codespace on `127.0.0.1:2323`. Both terminals
must be in the same Codespace; no browser port forwarding is needed. To run a
finite demo, use `bash scripts/run-server.sh 2323 20` (20 frames per connection).
Stop the listener with Ctrl+C. `python3 scripts/check-server.py` checks the server
setup without relying on the student client.

## What goes where

| Path | Purpose |
| --- | --- |
| `include/nyan/`, `src/` | Declared interfaces and student implementations |
| `src/telnet/` | Wire encoding, incremental parsing, option negotiation |
| `tests/` | Component and integration checks added with the work |
| [docs/design.md](docs/design.md) | Shared contracts and completion criteria |
| [docs/roadmap.md](docs/roadmap.md) | Tasks, difficulty, and dependencies |
| `.devcontainer/` | Default Linux development environment |
| `.github/workflows/ci.yml` | Build the same image and run checks on PRs |

Our environment builds upstream revision
[`32fd2eb`](https://github.com/klange/nyancat/tree/32fd2eb40332ae0001995705f0c1f8de69a2d543).
Its source and license remain in `/opt/nyancat` inside the container. Upstream's
`-t` mode uses stdin/stdout; socat provides the TCP listener. The animation and
upstream code belong to their original authors; see
[upstream's credits and license](https://github.com/klange/nyancat#licenses-references-etc).
