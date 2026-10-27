FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

# Compiler, build tools, and raylib dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    build-essential \
    git \
    git-lfs \
    cmake \
    pkg-config \
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
    && rm -rf /var/lib/apt/lists/*

# Download and build raylib
RUN git clone --depth 1 \
    https://github.com/raysan5/raylib.git /tmp/raylib \
    && make -C /tmp/raylib/src PLATFORM=PLATFORM_DESKTOP \
    && make -C /tmp/raylib/src install \
    && ldconfig \
    && rm -rf /tmp/raylib

WORKDIR /app

# Compile your application with:
# gcc main.c -o game -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

