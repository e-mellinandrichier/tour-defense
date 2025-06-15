#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <vector>

const int TILE_SIZE = 64;
const int MAP_WIDTH = 11;
const int MAP_HEIGHT = 12;

extern int map[MAP_HEIGHT][MAP_WIDTH];
std::vector<sf::Vector2i> getPathFromMap(int map[MAP_HEIGHT][MAP_WIDTH]);

#endif
