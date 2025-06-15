#ifndef TOUR_HPP
#define TOUR_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "dino.hpp"

class Tour {
public:
    Tour(sf::Vector2i gridPos);
    void update(std::vector<Dino*>& dinos);
    void draw(sf::RenderWindow& window);
    sf::Vector2i getGridPosition() const;

private:
    sf::Vector2f position;
    float range;
    float damage;
    float fireRate;
    sf::Clock fireClock;
    sf::RectangleShape shape;
};

#endif
