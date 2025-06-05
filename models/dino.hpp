#ifndef DINO_HPP
#define DINO_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Dino {
public:
    Dino(const std::vector<sf::Vector2i>& path);

    void update();
    void draw(sf::RenderWindow& window);
    void takeDamage(float amount);

    bool alive;

private:
    void updateHealthBar();

    float health;
    float speed;
    sf::Vector2f position;

    std::vector<sf::Vector2i> path;
    size_t currentIndex;

    sf::RectangleShape shape;
    sf::RectangleShape healthBarBack;
    sf::RectangleShape healthBarFront;
};

#endif
