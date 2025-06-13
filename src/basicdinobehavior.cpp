#include "basicdinobehavior.hpp"
#include <cmath>

void BasicDinoBehavior::move(sf::Vector2f& position, const sf::Vector2f& target, float speed, float deltaTime) {
    sf::Vector2f direction = target - position;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length != 0) {
        sf::Vector2f normalized = direction / length;
        position += normalized * speed * deltaTime;

        if ((target - position).x * normalized.x < 0 || (target - position).y * normalized.y < 0) {
            position = target;
        }
    }
}
