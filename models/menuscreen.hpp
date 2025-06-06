#ifndef MENUSCREEN_HPP
#define MENUSCREEN_HPP

#include <SFML/Graphics.hpp>

class MenuScreen {
public:
    MenuScreen(sf::RenderWindow& window);
    void draw();

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Text menuText;
};

#endif
