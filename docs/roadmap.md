# Work plan

Milestone: [v0.1 — First cat over TCP](https://github.com/A-Programming-Club/nyancat-network/milestone/1).

**Ready to claim now:** [#1](https://github.com/A-Programming-Club/nyancat-network/issues/1), [#2](https://github.com/A-Programming-Club/nyancat-network/issues/2), [#3](https://github.com/A-Programming-Club/nyancat-network/issues/3), [#11](https://github.com/A-Programming-Club/nyancat-network/issues/11), [#15](https://github.com/A-Programming-Club/nyancat-network/issues/15). Comment on the issue; an organizer can assign you.

Easy tasks suit a first PR; medium tasks introduce a new API; hard tasks require
reasoning about state, I/O, or integration. Pairing on hard tasks is encouraged.
Dependencies describe merge order. Read ahead freely, but start implementation
when its required components have landed.

| Task | Difficulty | Merge first |
| --- | --- | --- |
| [#1 Add Telnet wire constants to constants.h](https://github.com/A-Programming-Club/nyancat-network/issues/1) | easy | None |
| [#2 Parse host, port, and --help in cli.cpp](https://github.com/A-Programming-Club/nyancat-network/issues/2) | easy | None |
| [#3 Implement move-only socket ownership in socket.cpp](https://github.com/A-Programming-Club/nyancat-network/issues/3) | medium | None |
| [#4 Resolve a hostname and open a TCP connection in connect.cpp](https://github.com/A-Programming-Club/nyancat-network/issues/4) | medium | [#3](https://github.com/A-Programming-Club/nyancat-network/issues/3) |
| [#5 Handle partial reads and writes in io.cpp](https://github.com/A-Programming-Club/nyancat-network/issues/5) | medium | [#3](https://github.com/A-Programming-Club/nyancat-network/issues/3) |
| [#6 Encode Telnet commands and subnegotiations in encode.cpp](https://github.com/A-Programming-Club/nyancat-network/issues/6) | easy | [#1](https://github.com/A-Programming-Club/nyancat-network/issues/1) |
| [#7 Decode fragmented Telnet streams in parser.cpp](https://github.com/A-Programming-Club/nyancat-network/issues/7) | hard | [#1](https://github.com/A-Programming-Club/nyancat-network/issues/1) |
| [#8 Build the terminal-type reply in terminal_type.cpp](https://github.com/A-Programming-Club/nyancat-network/issues/8) | easy | [#6](https://github.com/A-Programming-Club/nyancat-network/issues/6) |
| [#9 Encode terminal dimensions in window_size.cpp](https://github.com/A-Programming-Club/nyancat-network/issues/9) | medium | [#6](https://github.com/A-Programming-Club/nyancat-network/issues/6) |
| [#10 Negotiate nyancat's Telnet options in session.cpp](https://github.com/A-Programming-Club/nyancat-network/issues/10) | hard | [#8](https://github.com/A-Programming-Club/nyancat-network/issues/8), [#9](https://github.com/A-Programming-Club/nyancat-network/issues/9) |
| [#11 Write animation bytes and read terminal size in terminal.cpp](https://github.com/A-Programming-Club/nyancat-network/issues/11) | medium | None |
| [#12 Connect the components into the client in main.cpp](https://github.com/A-Programming-Club/nyancat-network/issues/12) | medium | [#2](https://github.com/A-Programming-Club/nyancat-network/issues/2), [#4](https://github.com/A-Programming-Club/nyancat-network/issues/4), [#5](https://github.com/A-Programming-Club/nyancat-network/issues/5), [#7](https://github.com/A-Programming-Club/nyancat-network/issues/7), [#10](https://github.com/A-Programming-Club/nyancat-network/issues/10), [#11](https://github.com/A-Programming-Club/nyancat-network/issues/11) |
| [#13 Exit cleanly on Ctrl+C during playback and idle reads](https://github.com/A-Programming-Club/nyancat-network/issues/13) | hard | [#12](https://github.com/A-Programming-Club/nyancat-network/issues/12) |
| [#14 Test the real client against upstream nyancat with CTest](https://github.com/A-Programming-Club/nyancat-network/issues/14) | hard | [#13](https://github.com/A-Programming-Club/nyancat-network/issues/13) |
| [#15 Document the real nyancat handshake in docs/protocol.md](https://github.com/A-Programming-Club/nyancat-network/issues/15) | easy | None |

After constants land, the parser and encoder can proceed in parallel. The
terminal-type and window-size tasks can then proceed independently. Networking
and terminal output can be developed alongside the protocol work. The main
integration task brings those pieces together.

Organizers: assign members after they claim a task, review small PRs, and merge
prerequisites first. The fork workflow needs no organization write access for
contributors. Keep discussions and progress in the linked issues. The milestone
is complete when the real-server client demo, error handling, and integration
checks in [the design](design.md#done-means) all work.
