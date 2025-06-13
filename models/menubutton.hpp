// MenuButton.hpp
#ifndef MENUBUTTON_HPP
#define MENUBUTTON_HPP

#include <SFML/Graphics.hpp>

class MenuButton {
public:
    MenuButton(const std::string& label, const sf::Font& font, unsigned int size, sf::Vector2f position);

    void draw(sf::RenderWindow& window) const;
    void setSelected(bool selected);
    const sf::Text& getText() const;
    std::string getLabel() const;

private:
    sf::Text text;
    sf::Text label;

};

#endif