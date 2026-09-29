# The first working client

We are building a receive-only client for
[klange/nyancat](https://github.com/klange/nyancat/tree/32fd2eb40332ae0001995705f0c1f8de69a2d543).
The C++ process connects directly to TCP, handles the subset of telnet used by
that server, and sends its animation bytes to stdout. No subprocess running
`telnet`, `nc`, or `socat` inside the client; socat belongs to the development
server. No animation assets or terminal emulator need to be written.

## Data flow

```text
arguments → connect_tcp → receive → Parser → data → write_terminal
                                      │
                                      └→ option events → Session → send_all
```

TCP transports an ordered byte stream. One `recv` can contain half a command,
many commands, or animation mixed with commands. ANSI escapes are animation
data; telnet commands are protocol data. They are different byte sequences.

Headers declare the shared interfaces so tasks can be developed separately.
Their `.cpp` files initially contain TODOs, not implementations. Calling an
unfinished function will fail to link. `main.cpp` is a temporary reminder until
the integration task lands. Add private members to `Parser` and `Session` as
needed; discuss changes to public signatures on the dependent issues.

## Contracts

| Component | Required behavior |
| --- | --- |
| CLI | `nyancat-client [host [port]]` or `nyancat-client --help`. Defaults: `127.0.0.1`, `2323`. Port is decimal 1–65535. Reject empty host, flags other than standalone `--help`, extra arguments, and malformed ports. |
| Socket | One owner for an fd. `-1` is empty; fd `0` is valid. Move transfers ownership. Destruction closes once. `release` hands ownership to the caller; `reset` replaces it. |
| Connect | Resolve host and numeric service for TCP with IPv4/IPv6 support, try returned addresses, and release failed attempts and resolver memory. Errors include useful context. |
| I/O | `receive` returns only the byte count read; zero means EOF. Empty receive buffers are rejected. Retry `EINTR`; other errors throw. `send_all` handles short sends and `EINTR`, permits empty output, and uses Linux `MSG_NOSIGNAL`. |
| Parser | Emit ordered `Event`s for data, option negotiation, and subnegotiation. Preserve state between calls; remove telnet framing and unescape doubled IAC bytes. Data event grouping is unspecified. |
| Session | Keep client and server option states separately. React to server requests; do not initiate unsolicited negotiation. Return wire replies, never print them. |
| Terminal | Write exact byte counts and flush promptly; preserve ANSI escapes and embedded NULs. Report write errors. Read initial dimensions with `TIOCGWINSZ`, falling back to 80×24. Cleanup restores colors and cursor only for a TTY. |

Use exceptions for errors: `std::invalid_argument` for bad caller input,
`std::system_error` for errors described by `errno`, and `std::runtime_error` for
resolver/protocol errors. Destructors and best-effort terminal cleanup never
throw. `main` catches errors and prints a short message to **stderr**.

The scoped parser preserves ordinary data bytes, including upstream's
`CR NUL LF` line endings. The terminal handles those. We do not claim to implement
every NVT translation, interactive keyboard forwarding, or the BINARY option.
Ignore single-byte telnet commands such as NOP; malformed subnegotiation and
truncated commands at EOF are errors. Cap decoded subnegotiation payloads at
1024 bytes and reject larger ones. No buffering of complete animation frames.

## Options we support

| Server request | Client policy |
| --- | --- |
| `WILL SUPPRESS-GO-AHEAD` | Accept the server's option. |
| `DO SUPPRESS-GO-AHEAD` | Accept the client's option. |
| `DO TERMINAL-TYPE` | Agree; answer a subsequent `SEND` with `xterm-256color`. |
| `DO NAWS` | Agree and send initial columns/rows in network byte order. |
| Other `WILL` / `DO` requests | Refuse the unsupported option. |
| `WONT` / `DONT` | Disable that direction; acknowledge only if it was enabled. |

Repeated requests for an already-enabled option produce no extra acknowledgment.
Refuse unsupported requests, but do not respond to their negative acknowledgment.
Only answer terminal-type subnegotiation while that option is enabled. Ignore
unknown subnegotiations after the parser consumes them. The session is passive,
so proactive option changes and the full RFC 1143 negotiation algorithm are out
of scope.

Read the pinned upstream `set_options()` and handshake in
[`src/nyancat.c`](https://github.com/klange/nyancat/blob/32fd2eb40332ae0001995705f0c1f8de69a2d543/src/nyancat.c).
It negotiates at startup and then renders; send size before playback. Live
resize is outside this milestone because this upstream server does not keep
reading NAWS messages during animation.

## Done means

- In two Codespace terminals, the provided server and our C++ client display an
  animated, colored cat. The client sends valid telnet replies over its socket.
- `--help` exits 0 without connecting; invalid arguments exit 2; connection,
  protocol, and I/O errors exit 1; clean server EOF exits 0.
- Ctrl+C during playback or an idle receive exits 130 promptly and restores the
  visible cursor and normal colors. Local terminal input mode stays unchanged.
- Component checks cover meaningful failure cases; an automated test runs the
  real upstream server and built client. No public telnet host is required.

The initial blocking resolver/connect implementation has OS-controlled timeouts.
Cancellable DNS/connect and interactive input are future work. Ctrl+C handling
in this milestone covers the connected session, including an idle peer.

## Reading map

- [Telnet commands and negotiation: RFC 854](https://datatracker.ietf.org/doc/html/rfc854)
- [Option codes: IANA registry](https://www.iana.org/assignments/telnet-options/)
- [Terminal type: RFC 1091, §§2, 5, 8](https://datatracker.ietf.org/doc/html/rfc1091)
- [Window size: RFC 1073, §§2, 3](https://datatracker.ietf.org/doc/html/rfc1073)
- [Socket APIs: Linux man-pages](https://man7.org/linux/man-pages/man7/socket.7.html)
- [ANSI controls: XTerm reference](https://invisible-island.net/xterm/ctlseqs/ctlseqs.html)
