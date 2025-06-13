#include "dinofactory.hpp"
#include "linearbehavior.hpp"
#include "randomspeedstrategy.hpp"

std::unique_ptr<Dino> DinoFactory::createDino(const std::vector<sf::Vector2i>& path) {
    std::unique_ptr<DinoBehavior> behavior = std::make_unique<LinearBehavior>();
    std::unique_ptr<SpeedStrategy> speedStrategy = std::make_unique<RandomSpeedStrategy>();
    return std::make_unique<Dino>(path, std::move(behavior), std::move(speedStrategy));
}

