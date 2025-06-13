#ifndef NORMALBEHAVIOR_HPP
#define NORMALBEHAVIOR_HPP

#include "dinobehavior.hpp"
#include <SFML/System/Vector2.hpp>
#include <cmath>

class NormalBehavior : public DinoBehavior {
public:
    void move(sf::Vector2f& position, const sf::Vector2f& target, float speed) override {
        sf::Vector2f direction = target - position;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0) {
            direction /= length;
            position += direction * speed;
        }
    }
};

#endif
