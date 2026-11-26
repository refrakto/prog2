#!/usr/bin/env bash
set -euxo pipefail

raylib_version="${1:?Usage: build-raylib.sh RAYLIB_VERSION}"

# Clonar o codigo fonte do raylib.
git clone --depth 1 --branch "${raylib_version}" \
    https://github.com/raysan5/raylib.git /tmp/raylib

# Instalar o OBGGCC para gerar binarios compativeis com glibc 2.31
# (Ubuntu 20.04).
obggcc_tag="$(curl --connect-timeout 10 --retry 10 --retry-all-errors \
    --fail --silent --show-error --location \
    https://api.github.com/repos/AmanoTeam/obggcc/releases/latest | jq --exit-status --raw-output '.tag_name')"
curl --connect-timeout 10 --retry 10 --retry-all-errors --fail --silent \
    --show-error --location \
    "https://github.com/AmanoTeam/obggcc/releases/download/${obggcc_tag}/x86_64-unknown-linux-gnu.tar.xz" \
    --output /tmp/obggcc.tar.xz
tar --extract --file=/tmp/obggcc.tar.xz --directory=/opt
rm /tmp/obggcc.tar.xz

export OBGGCC_HOME=/opt/obggcc
target_apt="${OBGGCC_HOME}/bin/x86_64-unknown-linux-gnu2.31-apt"
target_cc="${OBGGCC_HOME}/bin/x86_64-unknown-linux-gnu2.31-gcc"
target_sysroot="$("${target_cc}" -print-sysroot)"
: "${target_sysroot:?OBGGCC did not report its target sysroot}"

"${target_apt}" install -y \
    libasound2-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libwayland-dev \
    libx11-dev \
    libxcursor-dev \
    libxinerama-dev \
    libxkbcommon-dev \
    libxrandr-dev \
    libxi-dev

# Compilar raylib para Linux usando o sysroot do Ubuntu 20.04.
cmake -S /tmp/raylib -B /tmp/build-linux -G Ninja \
    -DCMAKE_TOOLCHAIN_FILE="${OBGGCC_HOME}/build/cmake/x86_64-unknown-linux-gnu2.31.cmake" \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/usr \
    -DINCLUDE_EVERYTHING=ON
cmake --build /tmp/build-linux
DESTDIR="${target_sysroot}" cmake --install /tmp/build-linux

# Configurar CMAKE para utilizar MinGW UCRT64.
cat > /opt/toolchain-ucrt64.cmake <<'EOF'
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)
set(CMAKE_C_COMPILER x86_64-w64-mingw32ucrt-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32ucrt-g++)
set(CMAKE_RC_COMPILER x86_64-w64-mingw32ucrt-windres)
set(CMAKE_FIND_ROOT_PATH /usr/x86_64-w64-mingw32ucrt)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
EOF

# Compilar e instalar raylib para MinGW UCRT64.
cmake -S /tmp/raylib -B /tmp/build-win -G Ninja \
    -DCMAKE_TOOLCHAIN_FILE=/opt/toolchain-ucrt64.cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/usr/x86_64-w64-mingw32ucrt
cmake --build /tmp/build-win
cmake --install /tmp/build-win

# Remove temporary source and build directories.
rm -rf /tmp/raylib /tmp/build-linux /tmp/build-win /opt/toolchain-ucrt64.cmake
