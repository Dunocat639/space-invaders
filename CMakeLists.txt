cmake_minimum_required(VERSION 3.20)
project(SpaceInvaders VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries" FORCE)
# set(BUILD_EXAMPLES OFF CACHE BOOL "Do not build raylib examples" FORCE)
# set(BUILD_GAMES OFF CACHE BOOL "Do not build raylib games" FORCE)
set(GLFW_BUILD_WAYLAND ON CACHE BOOL "Build GLFW with Wayland support" FORCE)

# Si compilem per a Windows, forcem enllaçat estàtic del runtime C/C++ 
# perquè el joc no demani DLLs de MinGW al jugador
if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
endif()

# Busquem la instal·lació de raylib del sistema
find_package(raylib REQUIRED)

# --- DESCARREGA AUTOMÀTICA DESACTIVADA ---
# include(FetchContent)
# FetchContent_Declare(
#     raylib
#     GIT_REPOSITORY https://github.com/raysan5/raylib.git
#     GIT_TAG        6.0
# )
# FetchContent_MakeAvailable(raylib)

file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Copiar automàticament la carpeta assets/ al directori de l'executable si existeix
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/assets")
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CMAKE_CURRENT_SOURCE_DIR}/assets"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
        COMMENT "Copiant assets a la carpeta de sortida..."
    )
endif()