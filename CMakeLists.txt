cmake_minimum_required(VERSION 3.15)
project(SFMLTest)

# Chemin vers ton installation SFML
set(SFML_DIR "${CMAKE_SOURCE_DIR}/sfml-install/lib/cmake/SFML")

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(SFMLTest main.cpp)

target_link_libraries(SFMLTest PRIVATE sfml-graphics sfml-window sfml-system)

target_include_directories(SFMLTest PRIVATE ${SFML_INCLUDE_DIR})
