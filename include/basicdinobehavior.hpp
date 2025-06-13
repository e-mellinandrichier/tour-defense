#ifndef DINOBEHAVIOR_HPP
#define DINOBEHAVIOR_HPP

#include <SFML/System/Vector2.hpp>

class DinoBehavior {
public:
    virtual ~DinoBehavior() = default;

    virtual void move(sf::Vector2f& position, const sf::Vector2f& target, float speed, float deltaTime) = 0;
};

#endif
