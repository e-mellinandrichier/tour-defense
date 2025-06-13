#include "dino.hpp"
#include "dino_behavior.hpp"  // ou BasicDinoBehavior.hpp selon ton projet
#include <iostream>

Dino::Dino(const std::vector<sf::Vector2i>& path, std::unique_ptr<DinoBehavior> behavior)
    : path(path), behavior(std::move(behavior)), alive(true)
{
    shape.setSize(sf::Vector2f(50.f, 50.f));
    shape.setFillColor(sf::Color::Green);

    healthBarBack.setSize(sf::Vector2f(50.f, 5.f));
    healthBarBack.setFillColor(sf::Color(100, 100, 100));
    healthBarBack.setPosition(0.f, -10.f); // au-dessus du dino

    healthBarFront.setSize(sf::Vector2f(50.f, 5.f));
    healthBarFront.setFillColor(sf::Color::Red);
    healthBarFront.setPosition(0.f, -10.f);

    currentIndex = 0;
}

void Dino::update(float deltaTime) {
    if (!alive || path.empty())
        return;

    if (currentIndex >= path.size())
        return;

    // Position actuelle et suivante
    sf::Vector2f currentPos = shape.getPosition();
    sf::Vector2f targetPos(path[currentIndex].x * 64.f, path[currentIndex].y * 64.f);

    float speed = 100.f;

    sf::Vector2f direction = targetPos - currentPos;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance < 1.f) {
        // On est arrivé à la case suivante
        currentIndex++;
    } else {
        // Normaliser direction et déplacer
        sf::Vector2f movement = direction / distance * speed * deltaTime;
        shape.move(movement);
        healthBarBack.move(movement);
        healthBarFront.move(movement);
    }
}

void Dino::draw(sf::RenderWindow& window) {
    window.draw(shape);

    // Positionner les barres de vie par rapport au dino
    sf::Vector2f pos = shape.getPosition();
    healthBarBack.setPosition(pos.x, pos.y - 10.f);
    healthBarFront.setPosition(pos.x, pos.y - 10.f);

    window.draw(healthBarBack);
    window.draw(healthBarFront);
}

void Dino::takeDamage(float amount) {
    if (!alive)
        return;

    health -= amount;
    if (health <= 0.f) {
        health = 0.f;
        alive = false;
    }
    updateHealthBar();
}

void Dino::updateHealthBar() {
    float healthPercent = health / 100.f;
    healthBarFront.setSize(sf::Vector2f(50.f * healthPercent, 5.f));
}

bool Dino::isAlive() const {
    return alive;
}
