#ifndef LINEAR_BEHAVIOR_HPP
#define LINEAR_BEHAVIOR_HPP

#include "dinobehavior.hpp"
#include <cmath>

class LinearBehavior : public DinoBehavior {
public:
    void move(sf::Vector2f& position, const sf::Vector2f& target, float speed) override {
        sf::Vector2f direction = target - position;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length > 0.f) {
            direction /= length; 
            position += direction * speed;

            if ((target - position).x * direction.x < 0 || (target - position).y * direction.y < 0) {
                position = target;
            }
        } else {
            position = target;
        }
    }
};

#endif
