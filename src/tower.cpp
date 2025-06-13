#include "tower.hpp"

Tower::Tower(const sf::Vector2i& position)
    : position(position), level(1), range(100.0f), damage(10.0f) {}

void Tower::draw(sf::RenderWindow& window) const {
    sf::CircleShape shape(20);
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(position.x * 40 + 4, position.y * 40 + 4);
    window.draw(shape);
}

void Tower::upgrade() {
    level++;
    damage += 5.0f;
    range += 10.0f;
}

const sf::Vector2i& Tower::getPosition() const {
    return position;
}

int Tower::getLevel() const {
    return level;
}
