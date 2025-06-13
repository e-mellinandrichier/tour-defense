#include "menuscreen.hpp"
#include "ButtonFactory.hpp"
#include "../gamestate.hpp"
#include "map.hpp"
#include <iostream>
#include <optional>

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

    titleText.setFont(font);
    titleText.setString("MENU");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color::Red);
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.width / 2.f, titleBounds.height / 2.f);
    titleText.setPosition(window.getSize().x / 2.f, window.getSize().y / 6.f);

    buttons = ButtonFactory::createMenuButtons(font, window.getSize());
    buttons[selectedOption].setSelected(true);
}

void MenuScreen::draw() {
    window.draw(backgroundSprite);
    window.draw(titleText);
    for (const auto& btn : buttons)
        btn.draw(window);
}

std::optional<GameState> MenuScreen::handleInput(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        // Navigation entre les boutons
        buttons[selectedOption].setSelected(false);
        if (event.key.code == sf::Keyboard::Up) {
            if (selectedOption > 0) selectedOption--;
        } else if (event.key.code == sf::Keyboard::Down) {
            if (selectedOption < (int)buttons.size() - 1) selectedOption++;
        }
        buttons[selectedOption].setSelected(true);

        // Validation avec Espace
        if (event.key.code == sf::Keyboard::Space) {
            // std::cout << "run_game() lancé !" << std::endl;
            // std::cout << "Barre espace détectée dans MenuScreen" << std::endl;
            run_game();
            return getSelectedState(); // Renvoie GameState::Game si "Play" est sélectionné
        }
    }

    return std::nullopt;
}



std::optional<GameState> MenuScreen::getSelectedState() const {
    std::string label = buttons[selectedOption].getLabel();

    if (label == "Play") return GameState::Game;
    // else if (label == "Scores") return GameState::ScoreScreen;
    // else if (label == "Options") return GameState::OptionScreen;
    // else if (label == "Credits") return GameState::CreditsScreen;

    return std::nullopt;
}