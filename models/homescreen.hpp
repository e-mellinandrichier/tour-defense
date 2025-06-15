#ifndef HOMESCREEN_HPP
#define HOMESCREEN_HPP

#include <SFML/Graphics.hpp>
#include "gamestate.hpp"

class HomeScreen {
public:
    HomeScreen(sf::RenderWindow& window);
    GameState handleEvents(sf::Event& event);
    void update();
    void draw();

private:
    sf::RenderWindow& window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    sf::Text introText;
    sf::Clock clock;
};

#endif
