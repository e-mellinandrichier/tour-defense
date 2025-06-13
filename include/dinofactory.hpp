#ifndef DINO_FACTORY_HPP
#define DINO_FACTORY_HPP

#include <memory>
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "dino.hpp"

class DinoFactory {
public:
    static std::unique_ptr<Dino> createDino(const std::vector<sf::Vector2i>& path);
};

#endif
