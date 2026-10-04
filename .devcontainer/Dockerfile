FROM mcr.microsoft.com/devcontainers/base:ubuntu-24.04

RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
       g++ gcc make cmake ninja-build gdb git ca-certificates \
       socat inetutils-telnet python3 man-db manpages-dev \
       clangd-18 clang-format-18 clang-tidy-18 \
    && rm -rf /var/lib/apt/lists/*

# Build the actual upstream server at a fixed revision. Keep its source/license.
ARG NYANCAT_REV=32fd2eb40332ae0001995705f0c1f8de69a2d543
RUN git init /opt/nyancat \
    && git -C /opt/nyancat remote add origin https://github.com/klange/nyancat.git \
    && git -C /opt/nyancat fetch --depth=1 origin "${NYANCAT_REV}" \
    && git -C /opt/nyancat checkout --detach FETCH_HEAD \
    && make -C /opt/nyancat \
    && install -m 0755 /opt/nyancat/src/nyancat /usr/local/bin/nyancat
