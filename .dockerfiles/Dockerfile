FROM debian:trixie-slim

ENV DEBIAN_FRONTEND=noninteractive

# Native toolchain, dev libs for raylib (Linux), and the MinGW-w64 UCRT64
# cross-compilers (Windows x86_64, UCRT runtime) from Debian's own repos.
RUN apt-get update && apt-get install -y --no-install-recommends \
        # Native Linux compiler and headers
        build-essential \
        linux-libc-dev \
        # MinGW-w64 UCRT64 cross-compiler and linker tools
        gcc-mingw-w64-ucrt64 \
        g++-mingw-w64-ucrt64 \
        binutils-mingw-w64-ucrt64 \
        # Linux development libraries used to build raylib
        libasound2-dev \
        libx11-dev \
        libxrandr-dev \
        libxi-dev \
        libgl1-mesa-dev \
        libglu1-mesa-dev \
        libxcursor-dev \
        libxinerama-dev \
        libwayland-dev \
        libxkbcommon-dev \
        # Build system
        cmake \
        ninja-build \
        pkgconf \
        # C/C++ development and code-analysis tools
        clang \
        clang-format \
        clang-tidy \
        clangd \
        # Source control, shell, certificates, and privilege utility
        ca-certificates \
        git \
        git-lfs \
        bash \
        sudo \
    && rm -rf /var/lib/apt/lists/*

# Build raylib from source: once for Linux, once for Windows (UCRT64).
ARG RAYLIB_VERSION=5.5
COPY .dockerfiles/build-raylib.sh /tmp/build-raylib.sh
RUN bash /tmp/build-raylib.sh "${RAYLIB_VERSION}" \
    && rm /tmp/build-raylib.sh

# Non-root user
ARG USERNAME=vscode
RUN useradd -m -s /bin/bash ${USERNAME} \
    && echo "${USERNAME} ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/${USERNAME} \
    && chmod 0440 /etc/sudoers.d/${USERNAME}

USER ${USERNAME}
WORKDIR /workspaces