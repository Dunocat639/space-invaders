# Detecta el sistema operatiu automàticament ("linux" o "windows")
OS := os()

BUILD_DIR := if OS == "windows" { "build-win-native" } else { "build-linux" }
BUILD_CROSS_DIR := "build-win-cross"
EXEC_NAME := "SpaceInvaders"

default: run

# Automatically detect if we are on Windows or Linux to make the proper setup
setup:
    @just --justfile {{justfile()}} _setup-{{OS}}

_setup-linux:
    cmake -B {{BUILD_DIR}} -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++

_setup-windows:
    cmake -B {{BUILD_DIR}} -G Ninja

# Compile with build-linux or build-win-native
build:
    cmake --build {{BUILD_DIR}}

# Run the executable in function on the OS
run: build
    {{ if OS == "windows" { ".\\" + BUILD_DIR + "\\" + EXEC_NAME + ".exe" } else { "./" + BUILD_DIR + "/" + EXEC_NAME } }}

# Cross compilation (compile for Windows from Linux)
setup-cross:
    cmake -B {{BUILD_CROSS_DIR}} -G Ninja \
        -DCMAKE_SYSTEM_NAME=Windows \
        -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc \
        -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++

# Cross build (build for Windows from Linux)
build-cross:
    cmake --build {{BUILD_CROSS_DIR}}

# Compile the .exe for Windows and run it with Wine from Linux
run-cross: build-cross
    wine ./{{BUILD_CROSS_DIR}}/{{EXEC_NAME}}.exe


# Remove all the build directories
clean:
    cmake -E remove_directory {{BUILD_DIR}} {{BUILD_CROSS_DIR}}