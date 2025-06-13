#include "map.hpp"
#include "dino.hpp"
#include "basicdinobehavior.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <memory>

const int TILE_SIZE = 64;
const int MAP_WIDTH = 11;
const int MAP_HEIGHT = 12;
const int MENU_WIDTH = 200;

enum TileType {
    EMPTY,
    PATH,
    START,
    END
};

int initialMap[MAP_HEIGHT][MAP_WIDTH] = {
    {1,0,0,0,0,0,0,0,0,0,0},
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


Map::Map()
    : tileSize(TILE_SIZE), menuWidth(MENU_WIDTH),
      behavior(std::make_unique<BasicDinoBehavior>()),
      dino(std::vector<sf::Vector2i>{}, nullptr)
{
    grid.resize(MAP_HEIGHT, std::vector<int>(MAP_WIDTH, 0));
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            grid[y][x] = initialMap[y][x];
        }
    }

    path = getPathFromMap(grid);

    dino = Dino(path, std::move(behavior));
}

std::vector<sf::Vector2i> Map::getPathFromMap(const std::vector<std::vector<int>>& map) {
    std::vector<sf::Vector2i> path;

    sf::Vector2i current(-1, -1);
    for (int x = 0; x < MAP_WIDTH; ++x) {
        if (map[0][x] == PATH) {
            current = { x, 0 };
            break;
        }
    }

    if (current.x == -1) {
        std::cerr << "Erreur: point de départ non trouvé dans la première ligne !" << std::endl;
        return path;
    }

    path.push_back(current);

    std::vector<sf::Vector2i> directions = {
        {1, 0}, {0, 1}, {-1, 0}, {0, -1}
    };

    bool visited[MAP_HEIGHT][MAP_WIDTH] = {};
    visited[current.y][current.x] = true;

    while (true) {
        bool moved = false;

        for (auto dir : directions) {
            sf::Vector2i next = current + dir;

            if (next.x >= 0 && next.x < MAP_WIDTH &&
                next.y >= 0 && next.y < MAP_HEIGHT &&
                !visited[next.y][next.x] &&
                map[next.y][next.x] == PATH) {

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

bool Map::isClickInMenu(const sf::Vector2i& pos, const sf::RenderWindow& window) {
    return pos.x >= window.getSize().x - menuWidth;
}

void Map::update(float deltaTime) {
    dino.takeDamage(0.0f);
    dino.update(deltaTime);
}

void Map::draw(sf::RenderWindow& window) {
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
            tile.setPosition(x * tileSize, y * tileSize);

            if (grid[y][x] == PATH) {
                tile.setFillColor(sf::Color(200, 200, 0));
            } else if (grid[y][x] == EMPTY) {
                tile.setFillColor(sf::Color(100, 100, 100));
            } else {
                tile.setFillColor(sf::Color(255, 0, 0));
            }

            tile.setOutlineThickness(1);
            tile.setOutlineColor(sf::Color::Black);
            window.draw(tile);
        }
    }

    dino.draw(window);

    sf::RectangleShape menu(sf::Vector2f(menuWidth, MAP_HEIGHT * tileSize));
    menu.setPosition(MAP_WIDTH * tileSize, 0);
    menu.setFillColor(sf::Color(50, 50, 50));
    window.draw(menu);
}

bool Map::isDinoAlive() const {
    return dino.isAlive();
}

void run_game() {
    sf::RenderWindow window(sf::VideoMode(MAP_WIDTH * TILE_SIZE + MENU_WIDTH, MAP_HEIGHT * TILE_SIZE), "Volcanos VS Dinos");

    Map map;
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (map.isClickInMenu(mousePos, window)) {
                    std::cout << "Clic dans le menu tours à : " << mousePos.x << ", " << mousePos.y << std::endl;
                } else {
                    std::cout << "Clic dans la map à : " << mousePos.x << ", " << mousePos.y << std::endl;
                }
            }
        }

        float deltaTime = map.isDinoAlive() ? clock.restart().asSeconds() : 0.0f;

        window.clear();
        map.update(deltaTime);
        map.draw(window);
        window.display();
    }
}
