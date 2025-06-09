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

void startNextWave(int& waveNumber, int& dinosToSpawn, bool& waitingNextWave, sf::Clock& spawnClock) {
    waveNumber++;
    dinosToSpawn = 3 + waveNumber * 2;
    waitingNextWave = false;
    spawnClock.restart();
    std::cout << "=== Vague " << waveNumber << " ===" << std::endl;
}

void run_game() {
    sf::RenderWindow window(sf::VideoMode(MAP_WIDTH * TILE_SIZE + 200, MAP_HEIGHT * TILE_SIZE), "Volcanos VS Dinos");

    std::vector<sf::Vector2i> path = getPathFromMap(map);
    std::vector<Dino*> dinos;
    std::vector<Tour> tours;

    sf::Clock clock;
    sf::Clock spawnClock;
    sf::Clock waveClock;

    int currentWave = 0;
    int dinosToSpawn = 0;
    float spawnInterval = 1.5f;
    bool waitingNextWave = true;

    sf::RectangleShape sidebar(sf::Vector2f(200, MAP_HEIGHT * TILE_SIZE));
    sidebar.setPosition(MAP_WIDTH * TILE_SIZE, 0);
    sidebar.setFillColor(sf::Color(50, 50, 50));

    sf::RectangleShape addTowerButton(sf::Vector2f(180, 50));
    addTowerButton.setPosition(MAP_WIDTH * TILE_SIZE + 10, 20);
    addTowerButton.setFillColor(sf::Color(100, 100, 200));

    bool placingTower = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                if (addTowerButton.getGlobalBounds().contains(mousePos)) {
                    placingTower = true;
                    std::cout << "Placer une tour : cliquez sur la carte" << std::endl;
                } else if (placingTower && mousePos.x < MAP_WIDTH * TILE_SIZE) {
                    sf::Vector2i tilePos(mousePos.x / TILE_SIZE, mousePos.y / TILE_SIZE);
                    tours.emplace_back(tilePos);
                    placingTower = false;
                    std::cout << "Tour placée en : " << tilePos.x << ", " << tilePos.y << std::endl;
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
                } else {
                    tile.setFillColor(sf::Color(100, 100, 100));
                }

                tile.setOutlineThickness(1);
                tile.setOutlineColor(sf::Color::Black);
                window.draw(tile);
            }
        }

        if (waitingNextWave && waveClock.getElapsedTime().asSeconds() > 3.0f) {
            startNextWave(currentWave, dinosToSpawn, waitingNextWave, spawnClock);
        }

        if (!waitingNextWave && dinosToSpawn > 0 && spawnClock.getElapsedTime().asSeconds() > spawnInterval) {
            dinos.push_back(new Dino(path));
            dinosToSpawn--;
            spawnClock.restart();
        }

        for (auto& tour : tours) {
            tour.update(dinos);
            tour.draw(window);
        }

        for (auto it = dinos.begin(); it != dinos.end(); ) {
            Dino* dino = *it;
            dino->update();
            dino->draw(window);

            if (!dino->alive) {
                delete dino;
                it = dinos.erase(it);
            } else {
                ++it;
            }
        }

        if (!waitingNextWave && dinosToSpawn == 0 && dinos.empty()) {
            waitingNextWave = true;
            waveClock.restart();
        }

        window.draw(sidebar);
        window.draw(addTowerButton);

        window.display();
    }

    for (auto dino : dinos) {
        delete dino;
    }
}
