#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <optional>

class OptionsScreen {
public:
    // Passe maintenant une référence sur la musique
    OptionsScreen(sf::RenderWindow& window, sf::Music& backgroundMusic);
    void draw();
    std::optional<int> handleInput(const sf::Event& event);

private:
    sf::RenderWindow& window;
    sf::Music& backgroundMusic;
    sf::Font font;
    sf::Text volumeText;
    void updateVolumeText();
};