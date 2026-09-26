# Versió base recomanada per a CMake modern
cmake_minimum_required(VERSION 3.25)
project(SpaceInvaders VERSION 1.0 LANGUAGES C CXX)

# Exigim l'estàndard C++23 sense excepcions ni extensions "rares" de GNU
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Configurem GLFW (el motor de fons de raylib) perquè s'entengui de meravella amb Wayland
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(GLFW_BUILD_WAYLAND ON CACHE BOOL "Build GLFW with Wayland support" FORCE)
endif()

# AQUÍ ESTÀ LA CLAU OFFLINE:
# Forcem CMake a buscar la llibreria de raylib que ja tens instal·lada a les entranyes del teu sistema.
# Zero descàrregues.
find_package(raylib REQUIRED)

# Busquem tot el teu codi font. CONFIGURE_DEPENDS refresca el build si fiques fitxers nous.
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

# Li fiquem els flags de debug i warnings perquè el compilador et cridi si fas alguna xapussa
target_compile_options(${PROJECT_NAME} PRIVATE
    -O2
    -Wall
    -Wextra
    -Werror
    -Wpedantic
    -g
)

# Indiquem on tens les capçaleres del projecte
target_include_directories(${PROJECT_NAME} PRIVATE "include")

# Fem l'enllaç amb la llibreria raylib del teu sistema
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Si s'està creant l'exe per a Windows 11 (via MinGW al justfile)...
if(WIN32)
    # Hi incrustem tot el runtime de C i C++ a la força perquè l'exe sigui independent i no et demani DLLs
    target_link_options(${PROJECT_NAME} PRIVATE -static -static-libgcc -static-libstdc++)
endif()

# Màgia per moure els teus gràfics i sons al lloc correcte després de compilar
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/assets")
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CMAKE_CURRENT_SOURCE_DIR}/assets"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
        COMMENT "Movent els assets a la vora de l'executable..."
    )
endif()