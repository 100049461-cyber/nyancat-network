"""Check the provided server environment, independently of the unfinished client."""

from pathlib import Path
import os
import signal
import socket
import subprocess
import time


def main():
    root = Path(__file__).resolve().parent.parent
    with socket.socket() as reservation:
        reservation.bind(("127.0.0.1", 0))
        port = reservation.getsockname()[1]

    server = subprocess.Popen(
        ["bash", str(root / "scripts/run-server.sh"), str(port), "2"],
        start_new_session=True,
    )
    try:
        deadline = time.monotonic() + 10
        while True:
            if server.poll() is not None:
                raise RuntimeError("Server exited before accepting a connection")
            try:
                peer = socket.create_connection(("127.0.0.1", port), timeout=1)
                break
            except ConnectionRefusedError:
                if time.monotonic() >= deadline:
                    raise RuntimeError("Server did not start within 10 seconds") from None
                time.sleep(0.05)

        with peer:
            wire = bytearray()
            while True:
                remaining = deadline - time.monotonic()
                if remaining <= 0:
                    raise RuntimeError("Finite-frame server failed to finish")
                peer.settimeout(remaining)
                chunk = peer.recv(4096)
                if not chunk:
                    break
                wire.extend(chunk)
                if len(wire) > 1_000_000:
                    raise RuntimeError("Unexpectedly large two-frame stream")

        # These are properties of upstream telnet mode, not the client solution.
        if not wire.startswith(b"\xff"):
            raise RuntimeError("Missing initial Telnet command")
        if b"\x1b[" not in wire or b"You have nyaned" not in wire:
            raise RuntimeError("Server did not produce ANSI animation output")
        print(f"Upstream server check passed ({len(wire)} bytes; orderly EOF).")
    finally:
        try:
            os.killpg(server.pid, signal.SIGTERM)
        except ProcessLookupError:
            pass
        try:
            server.wait(timeout=3)
        except subprocess.TimeoutExpired:
            os.killpg(server.pid, signal.SIGKILL)
            server.wait()


if __name__ == "__main__":
    main()
