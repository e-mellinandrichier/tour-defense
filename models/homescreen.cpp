#include "homescreen.hpp"
#include <cmath>
#include <iostream>

HomeScreen::HomeScreen(sf::RenderWindow& win) : window(win) {
    if (!backgroundTexture.loadFromFile("assets/homescreenbg.jpg")) {
        std::cerr << "Erreur chargement image fond\n";
    }

    backgroundSprite.setTexture(backgroundTexture);
    float scaleX = (float)window.getSize().x / backgroundTexture.getSize().x;
    float scaleY = (float)window.getSize().y / backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleX, scaleY);

    if (!font.loadFromFile("assets/Pixelcraft.ttf")) {
        std::cerr << "Erreur chargement police\n";
    }

    introText.setFont(font);
    introText.setString("Press any key");
    introText.setCharacterSize(70);
    introText.setFillColor(sf::Color::White);

    sf::FloatRect bounds = introText.getLocalBounds();
    introText.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    introText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
}

GameState HomeScreen::handleEvents(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed) {
        return GameState::MenuScreen;
    }
    return GameState::HomeScreen;
}

void HomeScreen::update() {
    float time = clock.getElapsedTime().asSeconds();
    float scale = 1.0f + 0.05f * std::sin(time * 2.f);
    introText.setScale(scale, scale);
}

void HomeScreen::draw() {
    window.draw(backgroundSprite);
    window.draw(introText);
}
