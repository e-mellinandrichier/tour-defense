cmake_minimum_required(VERSION 3.16)
project(TowerDefense)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML COMPONENTS graphics window system REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/models)

file(GLOB SOURCES
    "*.cpp"
    "models/*.cpp"
)

add_executable(TowerDefense ${SOURCES})

target_link_libraries(TowerDefense
    sfml-graphics
    sfml-window
    sfml-system
)