# Fixem la versió mínima de CMake a la 3.25, que és una base perfecta per a "Modern CMake".
cmake_minimum_required(VERSION 3.25)

# Definim el nom del projecte (SpaceInvaders), la seva versió (1.0) i els llenguatges requerits (C i C++).
project(SpaceInvaders VERSION 1.0 LANGUAGES C CXX)

# Indiquem a CMake que volem fer servir l'estàndard modern C++23 en aquest projecte.
set(CMAKE_CXX_STANDARD 23)
# Fem que l'estàndard C++23 sigui obligatori; si el compilador (com g++) no l'admet, saltarà un error ràpid.
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Desactivem extensions privades del compilador (com gnu++23) per garantir que el codi segueix un estàndard 100% pur.
set(CMAKE_CXX_EXTENSIONS OFF)

# Forcem globalment que les llibreries del projecte es construeixin com a fitxers estàtics (.a o .lib).
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries" FORCE)
# Desactivem la construcció d'exemples integrats de raylib per estalviar uns minuts preciosos de CPU.
set(BUILD_EXAMPLES OFF CACHE BOOL "Do not build raylib examples" FORCE)
# Desactivem la construcció dels minijocs de prova de raylib pel mateix motiu.
set(BUILD_GAMES OFF CACHE BOOL "Do not build raylib games" FORCE)

# Comprovem si el sistema operatiu on s'està compilant (no on s'executarà) és estrictament Linux.
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Forcem que la part interna de raylib (GLFW) es construeixi prioritzant el suport nadiu a l'entorn Wayland.
    set(GLFW_BUILD_WAYLAND ON CACHE BOOL "Build GLFW with Wayland support" FORCE)
# Tanquem el bloc condicional per a Linux.
endif()

# Carreguem el mòdul natiu FetchContent, que és la millor eina per descarregar i construir llibreries des de zero.
include(FetchContent)
# Declarem el paquet extern i preparem la informació necessària perquè CMake sàpiga d'on treure'l.
FetchContent_Declare(
    # Etiquetem aquesta dependència internament sota el nom "raylib".
    raylib
    # Assignem l'URL oficial del repositori git on s'allotja el codi font original.
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    # Fixem explícitament el "tag" a la branca corresponent per estabilitat (pots mantenir la 6.0 que tenies si vols fer servir l'última build).
    GIT_TAG        6.0
# Tanquem el bloc de configuració de la declaració del paquet.
)
# Aquesta comanda executa finalment la descàrrega de raylib i fa que l'objectiu "raylib" estigui disponible per al nostre codi.
FetchContent_MakeAvailable(raylib)

# Busquem recursivament tots els fitxers C++ (.cpp) existents dins el directori "src/".
# CONFIGURE_DEPENDS fa una màgia molt útil: permet a CMake regenerar el projecte si afegeixes o esborres algun fitxer font.
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# Indiquem a CMake que generi el nostre executable anomenat "SpaceInvaders" integrant tots els fitxers .cpp escanejats.
add_executable(${PROJECT_NAME} ${SOURCES})

# Configurem de forma "privada" (només per al nostre codi) les opcions del compilador g++ i MinGW per al nostre executable.
target_compile_options(${PROJECT_NAME} PRIVATE
    # Activem tots els avisos "warnings" recomanats normals perquè no se'ns escapi res.
    -Wall
    # Hi sumem un munt d'avisos addicionals que no inclou l'opció anterior per cobrir-nos bé les espatlles.
    -Wextra
    # Exigim que el codi segueixi l'estàndard ISO de C++23 de la manera més estricta, ideal per anar aprenent.
    -Wpedantic
    # Generem símbols de *debug*, que faran que depuradors com GDB sàpiguen exactament a quina línia i variable estàs.
    -g
# Tanquem el llistat d'opcions de compilació de la diana (target).
)

# Indiquem on el teu projecte guarda les "headers" (capçaleres .h o .hpp) perquè el compilador les trobi directament.
target_include_directories(${PROJECT_NAME} PRIVATE "include")

# Enllacem de forma estàtica el nostre executable final amb el "target" raylib que ens ha preparat FetchContent anteriorment.
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Analitzem si la compilació va enfocada específicament al sistema operatiu Windows (ja sigui de forma nativa o cross-compiling).
if(WIN32)
    # L'opció clau per crear portabilitat: forcem l'enllaç estàtic dels runtimes del llenguatge i les matemàtiques de gcc (MinGW).
    # Això garanteix que l'executable no demani la clàssica "libstdc++-6.dll" i es pugui obrir de bones a primeres arreu.
    target_link_options(${PROJECT_NAME} PRIVATE -static -static-libgcc -static-libstdc++)
    
    # OPCIONALMENT PODERÓS: Aquesta línia evita que s'obri una consola negra al fons cada vegada que algú clica el teu executable a Windows.
    # Descomenta aquesta línia només quan deixis de depurar al joc, perquè amaga el "std::cout".
    # set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE ON)
# Tanquem la comprovació de target cap a Windows.
endif()

# Mirem si dins de la carpeta actual del codi font hi tens un subdirectori sencer anomenat "assets".
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/assets")
    # Definim un esdeveniment que CMake ha d'executar automàticament JUST DESPRÉS de crear correctament l'executable "POST_BUILD".
    add_custom_command(
        # Apliquem aquesta operació especial només al moment post-compilació d'aquest executable concret.
        TARGET ${PROJECT_NAME} POST_BUILD
        # Demanem a l'eina interna independent del sistema operatiu de CMake que copii completament el directori d'una banda a una altra.
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                # L'origen del directori que has de copiar és literalment la carpeta de projecte on resideix el CMake actual.
                "${CMAKE_CURRENT_SOURCE_DIR}/assets"
                # Destinació: posem els "assets" al mateix nivell exacte d'on cau el binari acabat de crear.
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
        # Imprimeix aquest comentari currat al terminal perquè sàpigues visualment que les textures i música s'estan col·locant.
        COMMENT "Copiant assets a la carpeta de sortida per no liar-la amb els camins relatius del codi..."
    # Concloem la comanda per accions extres personalitzades de la diana.
    )
# Tanquem el condicional d'existència d'assets.
endif()