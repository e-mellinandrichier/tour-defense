#include "homescreen.hpp"
#include <cmath>
#include <iostream>

HomeScreen::HomeScreen(sf::RenderWindow& window)
{
    if (!loadAssets()) {
        std::cerr << "Erreur : chargement des assets échoué." << std::endl;
    }

    // Mise à l'échelle du fond
    float scaleX = static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleX, scaleY);

    // Texte intro
    introText.setFont(font);
    introText.setString("Appuyez sur une touche");
    introText.setCharacterSize(40);
    introText.setFillColor(sf::Color::White);
    sf::FloatRect introBounds = introText.getLocalBounds();
    introText.setOrigin(introBounds.width / 2, introBounds.height / 2);
    introText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

    // Texte menu
    menuText.setFont(font);
    menuText.setString("MENU PRINCIPAL");
    menuText.setCharacterSize(50);
    menuText.setFillColor(sf::Color::Yellow);
    sf::FloatRect menuBounds = menuText.getLocalBounds();
    menuText.setOrigin(menuBounds.width / 2, menuBounds.height / 2);
    menuText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
}

bool HomeScreen::loadAssets()
{
    bool ok = true;
    if (!backgroundTexture.loadFromFile("assets/homescreenbg.jpg")) {
        std::cerr << "Erreur : impossible de charger homescreenbg.jpg" << std::endl;
        ok = false;
    }

    if (!font.loadFromFile("assets/Pixelcraft.ttf")) {
        std::cerr << "Erreur : impossible de charger Daydream.ttf" << std::endl;
        ok = false;
    }

    backgroundSprite.setTexture(backgroundTexture);
    return ok;
}

void HomeScreen::handleEvent(const sf::Event& event, GameState& state)
{
    if ((event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed)
        && state == GameState::Intro) {
        state = GameState::Menu;
    }
}

void HomeScreen::update(GameState state)
{
    if (state == GameState::Intro) {
        float time = clock.getElapsedTime().asSeconds();
        float scale = 1.0f + 0.05f * std::sin(time * 2.f);
        introText.setScale(scale, scale);
    }
}

void HomeScreen::draw(sf::RenderWindow& window, GameState state)
{
    window.draw(backgroundSprite);
    if (state == GameState::Intro) {
        window.draw(introText);
    } else if (state == GameState::Menu) {
        window.draw(menuText);
    }
}
