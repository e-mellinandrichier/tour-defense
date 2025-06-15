#include "../models/map.hpp"

enum TileType { EMPTY, PATH, START, END };

int map[MAP_HEIGHT][MAP_WIDTH] = {
    {0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,1,0},
    {0,0,0,0,0,0,0,0,0,1,0},
    {0,0,0,0,0,0,1,1,1,1,0},
    {0,0,0,0,0,0,1,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,0,0},
    {0,0,1,1,1,1,1,0,0,0,0},
    {0,0,1,0,0,0,0,0,0,0,0}
};

std::vector<sf::Vector2i> getPathFromMap(int map[MAP_HEIGHT][MAP_WIDTH]) {
    std::vector<sf::Vector2i> path;
    sf::Vector2i current;
    for (int x = 0; x < MAP_WIDTH; ++x)
        if (map[0][x] == PATH) { current = { x, 0 }; break; }

    path.push_back(current);
    std::vector<sf::Vector2i> dirs = { {1,0},{0,1},{-1,0},{0,-1} };
    bool visited[MAP_HEIGHT][MAP_WIDTH] = {};
    visited[current.y][current.x] = true;

    while (true) {
        bool moved = false;
        for (auto dir : dirs) {
            sf::Vector2i next = current + dir;
            if (next.x >= 0 && next.x < MAP_WIDTH && next.y >= 0 && next.y < MAP_HEIGHT
                && !visited[next.y][next.x] && map[next.y][next.x] == PATH) {
                current = next;
                path.push_back(current);
                visited[current.y][current.x] = true;
                moved = true;
                break;
            }
        }
        if (!moved) break;
    }
    return path;
}
