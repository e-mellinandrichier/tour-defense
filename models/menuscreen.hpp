#ifndef MENUSCREEN_HPP
#define MENUSCREEN_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "menubutton.hpp"
#include <optional>
#include "gamestate.hpp"

class MenuScreen {
public:
    MenuScreen(sf::RenderWindow& window);
    void draw();
    std::optional<GameState> handleInput(sf::Event event);

private:
    sf::RenderWindow& window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    sf::Text titleText;
    std::vector<MenuButton> buttons;
    int selectedOption = 0;
    std::optional<GameState> getSelectedState() const;
};

#endif
