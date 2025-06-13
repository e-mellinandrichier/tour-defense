#include <vector>
#include <SFML/Graphics.hpp>
#include "menubutton.hpp"
#include <optional>
#include "../gamestate.hpp"




class MenuScreen {
private:
    sf::RenderWindow& window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;

    sf::Text titleText;
    std::vector<sf::Text> options;
    std::vector<MenuButton> buttons; 
    std::optional<GameState> getSelectedState() const;
    int selectedOption = 0;

public:
    MenuScreen(sf::RenderWindow& win);
    void draw();
    void handleInput(sf::Event event);
};
