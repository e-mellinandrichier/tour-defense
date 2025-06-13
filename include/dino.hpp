#ifndef DINO_HPP
#define DINO_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class DinoBehavior; 

class Dino {
public:
    Dino(const std::vector<sf::Vector2i>& path, std::unique_ptr<DinoBehavior> behavior);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

    void takeDamage(float amount);
    bool isAlive() const;

private:
    std::vector<sf::Vector2i> path;
    size_t currentIndex = 0;

    std::unique_ptr<DinoBehavior> behavior;

    sf::RectangleShape shape;

    float health = 100.f;
    sf::RectangleShape healthBarBack;
    sf::RectangleShape healthBarFront;

    bool alive = true;

    void updateHealthBar();
};

#endif 
