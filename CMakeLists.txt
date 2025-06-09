cmake_minimum_required(VERSION 3.16)
project(TowerDefense)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/models)

add_executable(TowerDefense
    main.cpp
    models/map.cpp
    models/dino.cpp
    models/tour.cpp
)

target_link_libraries(TowerDefense
    sfml-graphics
    sfml-window
    sfml-system
)
