#ifndef BUTTONFACTORY_HPP
#define BUTTONFACTORY_HPP

#include "menubutton.hpp"
#include <vector>

class ButtonFactory {
public:
    static std::vector<MenuButton> createMenuButtons(const sf::Font& font, sf::Vector2u windowSize);
};

#endif
