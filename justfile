BUILD_DIR := "build"
BUILD_WIN_DIR := "build-win"
EXEC_NAME := "SpaceInvaders"

default: run

# Setup per compilar a Linux
setup:
    cmake -B {{BUILD_DIR}} -G Ninja -DCMAKE_CXX_COMPILER=g++

# Setup per cross-compilar a Windows des de Linux (utilitzant MinGW)
setup-win:
    cmake -B {{BUILD_WIN_DIR}} -G Ninja \
        -DCMAKE_SYSTEM_NAME=Windows \
        -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc \
        -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++

# Compila per a Linux
build:
    cmake --build {{BUILD_DIR}}

# Compila per a Windows (.exe)
build-win:
    cmake --build {{BUILD_WIN_DIR}}

# Compila i executa a Linux
run: build
    ./{{BUILD_DIR}}/{{EXEC_NAME}}

# Neteja tots els directoris de compilació
clean:
    rm -rf {{BUILD_DIR}} {{BUILD_WIN_DIR}}