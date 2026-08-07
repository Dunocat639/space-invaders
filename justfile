# Carrega variables per defecte (pots canviar-ho si vols)
BUILD_DIR := "build"
EXEC_NAME := "SpaceInvaders"

# Per defecte, si només posa 'just', executarà la primera recepta (run)
default: run

# Configura CMake usant Ninja i g++ (només cal fer-ho 1 cop)
setup:
    cmake -B {{BUILD_DIR}} -G Ninja -DCMAKE_CXX_COMPILER=g++

# Compila
build:
    cmake --build {{BUILD_DIR}}

# Compila i executa
run: build
    ./{{BUILD_DIR}}/{{EXEC_NAME}}

# Netejar el directori /build
clean:
    rm -rf {{BUILD_DIR}}