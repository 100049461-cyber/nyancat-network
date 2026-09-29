#!/usr/bin/env bash
set -euo pipefail

# Optional second argument limits the frame count for automated checks.
port="${1:-2323}"
frames="${2:-0}"
if [[ $# -gt 2 || ! "$port" =~ ^[0-9]{1,5}$ || ! "$frames" =~ ^[0-9]{1,6}$ ]]; then
    echo "Usage: bash scripts/run-server.sh [port 1..65535] [frames 0..999999]" >&2
    exit 2
fi
port=$((10#$port))
frames=$((10#$frames))
if (( port < 1 || port > 65535 )); then
    echo "Port must be between 1 and 65535." >&2
    exit 2
fi
for tool in socat nyancat; do
    if ! command -v "$tool" >/dev/null; then
        echo "Missing $tool. Open this repository in its Codespace." >&2
        exit 1
    fi
done

echo "nyancat: 127.0.0.1:$port (Ctrl-C to stop the listener)" >&2
# -I skips the intro; -s leaves the terminal title alone. No PTY/line conversion:
# telnet commands and animation bytes must travel unchanged in both directions.
exec socat "TCP4-LISTEN:$port,bind=127.0.0.1,reuseaddr,fork" \
    "EXEC:nyancat -t -I -s -f $frames"
