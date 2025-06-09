#include "map.hpp"
#include "Dino.hpp"
#include "tour.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

const int TILE_SIZE = 64;
const int MAP_WIDTH = 11;
const int MAP_HEIGHT = 12;

enum TileType {
    EMPTY,
    PATH,
    START,
    END
};

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
    for (int x = 0; x < MAP_WIDTH; ++x) {
        if (map[0][x] == PATH) {
            current = { x, 0 };
            break;
        }
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

void run_game() {
    sf::RenderWindow window(sf::VideoMode(MAP_WIDTH * TILE_SIZE + 200, MAP_HEIGHT * TILE_SIZE), "Volcanos VS Dinos");

    std::vector<sf::Vector2i> path = getPathFromMap(map);
    Dino dino(path);

    std::vector<Tour> towers;
    bool placingTower = false;

    sf::Font font;
    font.loadFromFile("arial.ttf"); // assure-toi que ce fichier existe

    sf::RectangleShape sidebar(sf::Vector2f(200, MAP_HEIGHT * TILE_SIZE));
    sidebar.setPosition(MAP_WIDTH * TILE_SIZE, 0);
    sidebar.setFillColor(sf::Color(50, 50, 50));

    sf::RectangleShape addTowerBtn(sf::Vector2f(180, 50));
    addTowerBtn.setPosition(MAP_WIDTH * TILE_SIZE + 10, 30);
    addTowerBtn.setFillColor(sf::Color::Green);

    sf::Text addTowerText;
    addTowerText.setFont(font);
    addTowerText.setString("Ajouter Tour");
    addTowerText.setCharacterSize(18);
    addTowerText.setFillColor(sf::Color::Black);
    addTowerText.setPosition(MAP_WIDTH * TILE_SIZE + 20, 40);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (addTowerBtn.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    placingTower = true;
                    std::cout << "Mode placement de tour activé." << std::endl;
                } else if (placingTower) {
                    int x = mousePos.x / TILE_SIZE;
                    int y = mousePos.y / TILE_SIZE;

                    if (x >= 0 && x < MAP_WIDTH &&
                        y >= 0 && y < MAP_HEIGHT &&
                        map[y][x] == EMPTY) {

                        towers.emplace_back(sf::Vector2i(x, y));
                        std::cout << "Tour placée à : " << x << "," << y << std::endl;
                        placingTower = false;
                    } else {
                        std::cout << "❌ Emplacement invalide." << std::endl;
                    }
                }
            }
        }

        window.clear();

        for (int y = 0; y < MAP_HEIGHT; ++y) {
            for (int x = 0; x < MAP_WIDTH; ++x) {
                sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);

                if (map[y][x] == PATH) {
                    tile.setFillColor(sf::Color(200, 200, 0));
                } else if (map[y][x] == EMPTY) {
                    tile.setFillColor(sf::Color(100, 100, 100));
                } else {
                    tile.setFillColor(sf::Color(255, 0, 0));
                }

                tile.setOutlineThickness(1);
                tile.setOutlineColor(sf::Color::Black);
                window.draw(tile);
            }
        }

        // Mise à jour des tours
        std::vector<Dino*> dinos = { &dino };
        for (auto& tour : towers) {
            tour.update(dinos);
            tour.draw(window);
        }

        dino.update();
        dino.draw(window);

        window.draw(sidebar);
        window.draw(addTowerBtn);
        window.draw(addTowerText);

        window.display();
    }
}
