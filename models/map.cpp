#include "map.hpp"
#include "dino.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

const int TILE_SIZE = 64;
const int MAP_WIDTH = 11;
const int MAP_HEIGHT = 12;
const int PANEL_WIDTH = 200; // largeur du panneau latéral

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
    sf::RenderWindow window(sf::VideoMode(MAP_WIDTH * TILE_SIZE + PANEL_WIDTH, MAP_HEIGHT * TILE_SIZE), "Volcanos VS Dinos");

    std::vector<sf::Vector2i> path = getPathFromMap(map);
    Dino dino(path);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                std::cout << "Fermeture manuelle." << std::endl;
                window.close();
            }

            // Gestion du clic sur le bouton "Ajouter une tour"
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                sf::FloatRect btnBounds(MAP_WIDTH * TILE_SIZE + 10, 20, PANEL_WIDTH - 20, 50);

                if (btnBounds.contains(mousePos)) {
                    std::cout << "➕ Ajout d'une tour !" << std::endl;
                    // future logique d'ajout
                }
            }
        }

        window.clear();

        // Affichage de la carte
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

        // MAJ & affichage du Dino
        dino.takeDamage(0.0f);
        dino.update();
        dino.draw(window);

        // Panneau latéral
        sf::RectangleShape sidebar(sf::Vector2f(PANEL_WIDTH, MAP_HEIGHT * TILE_SIZE));
        sidebar.setPosition(MAP_WIDTH * TILE_SIZE, 0);
        sidebar.setFillColor(sf::Color(40, 40, 40));
        window.draw(sidebar);

        // Bouton "Ajouter une tour"
        sf::RectangleShape addTowerBtn(sf::Vector2f(PANEL_WIDTH - 20, 50));
        addTowerBtn.setPosition(MAP_WIDTH * TILE_SIZE + 10, 20);
        addTowerBtn.setFillColor(sf::Color::Green);
        window.draw(addTowerBtn);

        window.display();
    }
}
