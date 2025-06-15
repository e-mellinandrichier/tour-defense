cmake_minimum_required(VERSION 3.16)
project(TowerDefense)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Trouver SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Inclure les headers
include_directories(models)
include_directories(src)

# Liste des fichiers sources
add_executable(TowerDefense
    main.cpp
    src/dino.cpp
    src/map.cpp
    src/tour.cpp
    src/homescreen.cpp
    src/menuscreen.cpp
    src/menubutton.cpp
    src/buttonfactory.cpp
    src/game.cpp
)

# Lien SFML
target_link_libraries(TowerDefense
    sfml-graphics
    sfml-window
    sfml-system
)

# ---------- 🎯 Gestion automatique des assets 🎯 ----------

# On copie les assets à chaque génération de projet
add_custom_command(TARGET TowerDefense POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_BINARY_DIR}/assets
)
