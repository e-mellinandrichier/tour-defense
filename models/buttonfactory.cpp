// ButtonFactory.cpp
#include "ButtonFactory.hpp"

std::vector<MenuButton> ButtonFactory::createMenuButtons(const sf::Font& font, sf::Vector2u windowSize) {
    std::vector<MenuButton> buttons;
    std::vector<std::string> labels = { "Play", "Scores", "Options", "Credits" };

    for (size_t i = 0; i < labels.size(); ++i) {
        sf::Vector2f pos(windowSize.x / 2.f, windowSize.y / 2.f + i * 60);
        buttons.emplace_back(labels[i], font, 40, pos);
    }

    return buttons;
}