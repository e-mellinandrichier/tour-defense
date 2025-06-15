#include "../models/dino.hpp"
#include <cmath>
#include <random>
#include <iostream>

const int TILE_SIZE = 64;

Dino::Dino(const std::vector<sf::Vector2i>& path)
    : path(path), currentIndex(0), health(100.f), alive(true) {
    
    sf::Vector2i entry(path[0].x - 1, path[0].y);
    this->path.insert(this->path.begin(), entry);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.1f, 0.13f);
    speed = dist(gen);

    shape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    shape.setFillColor(sf::Color::Green);
    position = sf::Vector2f(this->path[0].x * TILE_SIZE, this->path[0].y * TILE_SIZE);
    shape.setPosition(position);

    healthBarBack.setSize(sf::Vector2f(TILE_SIZE, 5));
    healthBarBack.setFillColor(sf::Color(50, 50, 50));
    healthBarBack.setPosition(position.x, position.y - 10);

    healthBarFront.setSize(sf::Vector2f(TILE_SIZE, 5));
    healthBarFront.setPosition(position.x, position.y - 10);
    updateHealthBar();
}

void Dino::takeDamage(float amount) {
    health -= amount;
    if (health <= 0) {
        health = 0;
        alive = false;
    }
    updateHealthBar();
}

void Dino::updateHealthBar() {
    float ratio = health / 100.f;
    healthBarFront.setSize(sf::Vector2f(TILE_SIZE * ratio, 5));
    if (health > 75) healthBarFront.setFillColor(sf::Color::Green);
    else if (health > 50) healthBarFront.setFillColor(sf::Color::Yellow);
    else if (health > 25) healthBarFront.setFillColor(sf::Color(255, 165, 0));
    else healthBarFront.setFillColor(sf::Color::Red);
}

void Dino::update() {
    if (!alive) return;
    if (currentIndex + 1 >= path.size()) { alive = false; return; }
    sf::Vector2f target(path[currentIndex + 1].x * TILE_SIZE, path[currentIndex + 1].y * TILE_SIZE);
    sf::Vector2f dir = target - position;
    float dist = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (dist < speed) { currentIndex++; position = target; }
    else { dir /= dist; position += dir * speed; }
    shape.setPosition(position);
    healthBarBack.setPosition(position.x, position.y - 10);
    healthBarFront.setPosition(position.x, position.y - 10);
}

void Dino::draw(sf::RenderWindow& window) {
    if (!alive) return;
    window.draw(shape);
    window.draw(healthBarBack);
    window.draw(healthBarFront);
}

sf::Vector2f Dino::getPosition() const { return position; }
