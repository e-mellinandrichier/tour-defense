#include "../models/tour.hpp"
#include <cmath>

const int TILE_SIZE = 64;

Tour::Tour(sf::Vector2i gridPos) {
    position = sf::Vector2f(gridPos.x * TILE_SIZE, gridPos.y * TILE_SIZE);
    range = 128.0f;
    damage = 10.0f;
    fireRate = 1.0f;

    shape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(position);
}

void Tour::update(std::vector<Dino*>& dinos) {
    if (fireClock.getElapsedTime().asSeconds() < fireRate)
        return;

    for (Dino* dino : dinos) {
        if (!dino->alive) continue;
        sf::Vector2f dinoPos = dino->getPosition();
        float dx = dinoPos.x - position.x;
        float dy = dinoPos.y - position.y;
        float dist = std::sqrt(dx * dx + dy * dy);
        if (dist <= range) {
            dino->takeDamage(damage);
            fireClock.restart();
            break;
        }
    }
}

void Tour::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::Vector2i Tour::getGridPosition() const {
    return sf::Vector2i(position.x / TILE_SIZE, position.y / TILE_SIZE);
}
