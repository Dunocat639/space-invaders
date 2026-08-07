cmake_minimum_required(VERSION 3.20)
project(SpaceInvaders VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries" FORCE)

set(BUILD_EXAMPLES OFF CACHE BOOL "Do not build raylib examples" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "Do not build raylib games" FORCE)

set(GLFW_BUILD_WAYLAND ON CACHE BOOL "Build GLFW with Wayland support" FORCE)

# Incloem el mòdul de CMake per descarregar contingut extern
include(FetchContent)

# Definim d'on baixar Raylib (fem servir la versió estable 5.0)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        6.0
)

# Descarrega i afegeix Raylib al procés de compilació
FetchContent_MakeAvailable(raylib)

# El teu executable

file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

# Enllaçar Raylib
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)