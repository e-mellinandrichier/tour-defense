#include "menuscreen.hpp"
#include <iostream>

MenuScreen::MenuScreen(sf::RenderWindow& win) : window(win) {
    if (!backgroundTexture.loadFromFile("assets/menubg.jpg")) {
        std::cerr << "Erreur chargement image fond\n";
    }

    backgroundSprite.setTexture(backgroundTexture);
    float scaleX = (float)window.getSize().x / backgroundTexture.getSize().x;
    float scaleY = (float)window.getSize().y / backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleX, scaleY);
    if (!font.loadFromFile("assets/Pixelcraft.ttf")) {
        std::cerr << "Erreur chargement police\n";
    }

    menuText.setFont(font);
    
    menuText.setString("MENU");
    menuText.setCharacterSize(50);
    menuText.setFillColor(sf::Color::Red);

    sf::FloatRect bounds = menuText.getLocalBounds();
    menuText.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 1.f);
    menuText.setPosition(window.getSize().x / 2.f, window.getSize().y / 6.f);
}

void MenuScreen::draw() {
    window.draw(backgroundSprite);
    window.draw(menuText);
}
