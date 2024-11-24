# Minimum version of CMake
cmake_minimum_required(VERSION 3.10)

# Nom projet
project(Puissance4)

set(CMAKE_C_STANDARD 11)

# Fichiers sources
set(SOURCES
    src/main.c
    src/game/game_view.c
    src/game/game_back.c
)

# Chemins vers les en-têtes SFML
include_directories(${CMAKE_SOURCE_DIR}/includes)

# Chemins vers les bibliothèques CSFML
link_directories(${CMAKE_SOURCE_DIR}/libs/CSFML/lib)

# Répertoire des librairies SFML
# Trouve automatiquement les bibliothèques dynamiques
find_library(CSFML_GRAPHICS csfml-graphics HINTS ${CMAKE_SOURCE_DIR}/libs/CSFML/lib)
find_library(CSFML_WINDOW csfml-window HINTS ${CMAKE_SOURCE_DIR}/libs/CSFML/lib)
find_library(CSFML_SYSTEM csfml-system HINTS ${CMAKE_SOURCE_DIR}/libs/CSFML/lib)

if(NOT CSFML_GRAPHICS OR NOT CSFML_WINDOW OR NOT CSFML_SYSTEM)
    message(FATAL_ERROR "CSFML libraries not found")
endif()

# Ajout de l'exécutable
add_executable(Puissance4 ${SOURCES})

# Lier les bibliothèques CSFML
target_link_libraries(Puissance4 ${CSFML_GRAPHICS} ${CSFML_WINDOW} ${CSFML_SYSTEM})

# Répertoire de sortie
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# Copie des bibliothèques CSFML dans le dossier de l'exécutable
add_custom_command(TARGET Puissance4 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:Puissance4>/libs
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CSFML_GRAPHICS}
        ${CSFML_WINDOW}
        ${CSFML_SYSTEM}
        $<TARGET_FILE_DIR:Puissance4>/libs
)

# Ajustement des chemins pour les bibliothèques dynamiques (macOS)
get_filename_component(CSFML_GRAPHICS_BASENAME ${CSFML_GRAPHICS} NAME)
get_filename_component(CSFML_WINDOW_BASENAME ${CSFML_WINDOW} NAME)
get_filename_component(CSFML_SYSTEM_BASENAME ${CSFML_SYSTEM} NAME)

add_custom_command(TARGET Puissance4 POST_BUILD
    COMMAND install_name_tool
        -change ${CSFML_GRAPHICS} @executable_path/libs/${CSFML_GRAPHICS_BASENAME}
        -change ${CSFML_WINDOW} @executable_path/libs/${CSFML_WINDOW_BASENAME}
        -change ${CSFML_SYSTEM} @executable_path/libs/${CSFML_SYSTEM_BASENAME}
        $<TARGET_FILE:Puissance4>
)

# Copie des ressources (fonts et images)
set(FONT_DIR ${CMAKE_SOURCE_DIR}/font)
set(CONTENT_DIR ${CMAKE_SOURCE_DIR}/content)

set(DEST_DIR ${CMAKE_BINARY_DIR})

add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${FONT_DIR} ${DEST_DIR}/font
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CONTENT_DIR} ${DEST_DIR}/content
    COMMENT "Copying assets to build directory"
)

# Assure que la copie des assets est faite avant de lancer l'exécutable
add_dependencies(Puissance4 copy_assets)
