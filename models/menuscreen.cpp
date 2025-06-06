#include "menuscreen.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>


MenuScreen::MenuScreen(sf::RenderWindow& win) : window(win) {
    if (!backgroundTexture.loadFromFile("assets/menubg.jpg"))
        std::cerr << "Erreur chargement image fond\n";
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        (float)window.getSize().x / backgroundTexture.getSize().x,
        (float)window.getSize().y / backgroundTexture.getSize().y
    );

    if (!font.loadFromFile("assets/Pixelcraft.ttf"))
        std::cerr << "Erreur chargement police\n";

    // Titre
    titleText.setFont(font);
    titleText.setString("MENU");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color::Red);
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.width / 2.f, titleBounds.height / 2.f);
    titleText.setPosition(window.getSize().x / 2.f, window.getSize().y / 6.f);

    // Options
    std::vector<std::string> labels = { "Play","Scores", "Options", "Credits" };
    for (size_t i = 0; i < labels.size(); ++i) {
        sf::Text option;
        option.setFont(font);
        option.setString(labels[i]);
        option.setCharacterSize(40);
        option.setFillColor(i == selectedOption ? sf::Color::Yellow : sf::Color::White);
        sf::FloatRect bounds = option.getLocalBounds();
        option.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
        option.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f + i * 60);
        options.push_back(option);
    }
}

void MenuScreen::draw() {
    window.draw(backgroundSprite);
    window.draw(titleText);
    for (const auto& opt : options)
        window.draw(opt);
}

void MenuScreen::handleInput(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            if (selectedOption > 0) selectedOption--;
        } else if (event.key.code == sf::Keyboard::Down) {
            if (selectedOption < (int)options.size() - 1) selectedOption++;
        }

        // Met à jour les couleurs
        for (size_t i = 0; i < options.size(); ++i) {
            options[i].setFillColor(i == selectedOption ? sf::Color::Yellow : sf::Color::White);
        }
    }
}
