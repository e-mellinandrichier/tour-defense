#ifndef HOMESCREEN_HPP
#define HOMESCREEN_HPP

#include <SFML/Graphics.hpp>

enum class GameState {
    Intro,
    Menu
};

class HomeScreen {
public:
    HomeScreen(sf::RenderWindow& window);

    bool loadAssets();
    void handleEvent(const sf::Event& event, GameState& state);
    void update(GameState state);
    void draw(sf::RenderWindow& window, GameState state);

private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    sf::Text introText;
    sf::Text menuText;
    sf::Clock clock;
};

#endif // HOMESCREEN_HPP
