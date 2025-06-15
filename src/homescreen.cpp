#include "../models/homescreen.hpp"
#include <cmath>

HomeScreen::HomeScreen(sf::RenderWindow& win) : window(win) {
    backgroundTexture.loadFromFile("assets/homescreenbg.jpg");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        (float)window.getSize().x / backgroundTexture.getSize().x,
        (float)window.getSize().y / backgroundTexture.getSize().y
    );

    font.loadFromFile("assets/Pixelcraft.ttf");

    introText.setFont(font);
    introText.setString("Press any key");
    introText.setCharacterSize(70);
    introText.setFillColor(sf::Color::White);

    sf::FloatRect bounds = introText.getLocalBounds();
    introText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    introText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
}

GameState HomeScreen::handleEvents(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed)
        return GameState::MenuScreen;
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
