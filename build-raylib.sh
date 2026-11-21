#!/usr/bin/env bash
set -euxo pipefail

raylib_version="${1:?Usage: build-raylib.sh RAYLIB_VERSION}"

# Clonar codigo fonte do raylib.
git clone --depth 1 --branch "${raylib_version}" \
    https://github.com/raysan5/raylib.git /tmp/raylib

# Compilar and instalar raylib.
cmake -S /tmp/raylib -B /tmp/build-linux -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DINCLUDE_EVERYTHING=ON
cmake --build /tmp/build-linux
cmake --install /tmp/build-linux
ldconfig

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
rm -rf /tmp/raylib /tmp/build-linux /tmp/build-win
