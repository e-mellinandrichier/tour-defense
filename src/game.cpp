#include "../models/game.hpp"
#include <iostream>

Game::Game(sf::RenderWindow& win) : window(win), currentWave(0), dinosToSpawn(0),
    spawnInterval(1.5f), waitingNextWave(true), placingTower(false) {

    path = getPathFromMap(map);

    sidebar.setSize(sf::Vector2f(200, MAP_HEIGHT * TILE_SIZE));
    sidebar.setPosition(MAP_WIDTH * TILE_SIZE, 0);
    sidebar.setFillColor(sf::Color(50, 50, 50));

    addTowerButton.setSize(sf::Vector2f(180, 50));
    addTowerButton.setPosition(MAP_WIDTH * TILE_SIZE + 10, 20);
    addTowerButton.setFillColor(sf::Color(100, 100, 200));
}

void Game::startNextWave() {
    currentWave++;
    dinosToSpawn = 3 + currentWave * 2;
    waitingNextWave = false;
    spawnClock.restart();
    std::cout << "=== Vague " << currentWave << " ===" << std::endl;
}

void Game::handleEvents(sf::Event& event) {
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

void Game::update() {
    if (waitingNextWave && waveClock.getElapsedTime().asSeconds() > 3.0f)
        startNextWave();

    if (!waitingNextWave && dinosToSpawn > 0 && spawnClock.getElapsedTime().asSeconds() > spawnInterval) {
        dinos.push_back(new Dino(path));
        dinosToSpawn--;
        spawnClock.restart();
    }

    for (auto& tour : tours)
        tour.update(dinos);

    for (auto it = dinos.begin(); it != dinos.end(); ) {
        Dino* dino = *it;
        dino->update();

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
}

void Game::draw() {
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));
            tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);
            if (map[y][x] == 1)
                tile.setFillColor(sf::Color(200, 200, 0));
            else
                tile.setFillColor(sf::Color(100, 100, 100));

            tile.setOutlineThickness(1);
            tile.setOutlineColor(sf::Color::Black);
            window.draw(tile);
        }
    }

    for (auto& tour : tours)
        tour.draw(window);
    for (auto& dino : dinos)
        dino->draw(window);

    window.draw(sidebar);
    window.draw(addTowerButton);
}
