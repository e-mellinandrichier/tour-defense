#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Dino.hpp"
#include "BasicDinoBehavior.hpp"

class Map {
public:
    Map();

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

    bool isClickInMenu(const sf::Vector2i& pos, const sf::RenderWindow& window);

    bool isDinoAlive() const;

private:
    std::vector<std::vector<int>> grid;
    std::vector<sf::Vector2i> path;

    std::unique_ptr<DinoBehavior> behavior;
    Dino dino;

    int tileSize;
    int menuWidth;

    std::vector<sf::Vector2i> getPathFromMap(const std::vector<std::vector<int>>& map);
};

#endif
