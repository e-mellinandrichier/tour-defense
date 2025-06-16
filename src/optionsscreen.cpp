#include "optionsscreen.hpp"
#include <iostream>

OptionsScreen::OptionsScreen(sf::RenderWindow& win, sf::Music& music)
    : window(win), backgroundMusic(music)
{
    if (!font.loadFromFile("../assets/Pixelcraft.ttf")) {
        std::cerr << "Erreur chargement police\n";
    }
    volumeText.setFont(font);
    volumeText.setCharacterSize(30);
    volumeText.setPosition(100, 100);
    volumeText.setFillColor(sf::Color::White);
    updateVolumeText();
}

void OptionsScreen::draw() {
    // Fond gris foncé
    sf::RectangleShape background(sf::Vector2f(window.getSize()));
    background.setFillColor(sf::Color(30, 30, 30));
    
    // Instructions
    sf::Text instructions("left/right arrows to change volume", font, 24);
    instructions.setFillColor(sf::Color(200, 200, 200));
    instructions.setPosition(100, 200);

    // Dessiner tout
    window.draw(background);
    window.draw(volumeText);
    window.draw(instructions);
}

void OptionsScreen::updateVolumeText() {
    int vol = static_cast<int>(backgroundMusic.getVolume());
    volumeText.setString("Volume  " + std::to_string(vol) + "");
}

std::optional<int> OptionsScreen::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        float vol = backgroundMusic.getVolume();

        if (event.key.code == sf::Keyboard::Left) {
            vol = std::max(0.f, vol - 5.f);
            backgroundMusic.setVolume(vol);
        } 
        else if (event.key.code == sf::Keyboard::Right) {
            vol = std::min(100.f, vol + 5.f);
            backgroundMusic.setVolume(vol);
        } 
        else if (event.key.code == sf::Keyboard::Escape) {
            return 1; // Retour menu principal
        }

        updateVolumeText();
    }
    return std::nullopt;
}