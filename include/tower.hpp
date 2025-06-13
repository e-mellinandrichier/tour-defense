#ifndef TOWER_HPP
#define TOWER_HPP

#include <SFML/Graphics.hpp>

class Tower {
public:
    Tower(const sf::Vector2i& position);

    void draw(sf::RenderWindow& window) const;
    void upgrade();

    const sf::Vector2i& getPosition() const;
    int getLevel() const;

private:
    sf::Vector2i position;
    int level;
    float range;
    float damage;
};

#endif
