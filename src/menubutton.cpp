#include "../models/menubutton.hpp"

MenuButton::MenuButton(const std::string& label, const sf::Font& font, unsigned int size, sf::Vector2f position) {
    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(size);
    text.setFillColor(sf::Color::White);
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    text.setPosition(position);
}

void MenuButton::draw(sf::RenderWindow& window) const {
    window.draw(text);
}

void MenuButton::setSelected(bool selected) {
    text.setFillColor(selected ? sf::Color::Yellow : sf::Color::White);
}

const sf::Text& MenuButton::getText() const { return text; }
std::string MenuButton::getLabel() const { return text.getString(); }
