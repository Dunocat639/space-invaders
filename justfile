# Automatically detect the operating system ("linux" or "windows")
OS := os()

# Base directory for all builds and their specific subdirectories
BUILD_BASE_DIR := "build"
BUILD_DIR := if OS == "windows" { BUILD_BASE_DIR + "/windows" } else { BUILD_BASE_DIR + "/linux" }
BUILD_CROSS_DIR := BUILD_BASE_DIR + "/win-cross"
EXEC_NAME := "SpaceInvaders"

default: run

# Automatically detect if we are on Windows or Linux to set it up properly
setup:
    @just --justfile {{justfile()}} _setup-{{OS}}

_setup-linux:
    cmake -B {{BUILD_DIR}} -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++

_setup-windows:
    cmake -B {{BUILD_DIR}} -G Ninja

# Compile inside the current OS subdirectory (build/linux or build/win-native)
build:
    cmake --build {{BUILD_DIR}}

# Run the executable based on the active OS
run: build
    {{ if OS == "windows" { ".\\" + BUILD_DIR + "\\" + EXEC_NAME + ".exe" } else { "./" + BUILD_DIR + "/" + EXEC_NAME } }}

# ------------------------------------------------------------------------------
# CROSS-COMPILATION (Compile for Windows from Linux)
# ------------------------------------------------------------------------------
setup-cross:
    cmake -B {{BUILD_CROSS_DIR}} -G Ninja \
        -DCMAKE_SYSTEM_NAME=Windows \
        -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc \
        -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++

build-cross:
    cmake --build {{BUILD_CROSS_DIR}}

# Compile the Windows .exe and run it with Wine on Linux
run-cross: build-cross
    wine ./{{BUILD_CROSS_DIR}}/{{EXEC_NAME}}.exe


# Remove build directory
clean:
    cmake -E remove_directory {{BUILD_BASE_DIR}}