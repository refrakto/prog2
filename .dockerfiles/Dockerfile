FROM alpine:3.22
 
# Compilador, ferramentas de build e dependências do raylib
RUN apk add --no-cache \
    ca-certificates \
    build-base \
    clang \
    clang-extra-tools \
    linux-headers \
    git \
    git-lfs \
    cmake \
    pkgconf \
    alsa-lib-dev \
    libx11-dev \
    libxrandr-dev \
    libxi-dev \
    mesa-dev \
    glu-dev \
    libxcursor-dev \
    libxinerama-dev \
    wayland-dev \
    libxkbcommon-dev \
    bash \
    && sed -i 's#^root:\(.*\):/bin/ash$#root:\1:/bin/bash#' /etc/passwd
 
# Baixa e compila o raylib
RUN git clone --depth 1 \
    https://github.com/raysan5/raylib.git /tmp/raylib \
    && make -C /tmp/raylib/src PLATFORM=PLATFORM_DESKTOP \
    && make -C /tmp/raylib/src install \
    && rm -rf /tmp/raylib
 
WORKDIR /app
 
# Compile sua aplicação com:
# gcc main.c -o game -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
 
