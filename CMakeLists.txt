cmake_minimum_required(VERSION 3.16)
project(TowerDefense)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(models)
include_directories(src)

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

target_link_libraries(TowerDefense
    sfml-graphics
    sfml-window
    sfml-system
)
