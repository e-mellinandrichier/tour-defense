#include <vector>
#include <SFML/Graphics.hpp>


class MenuScreen {
private:
    sf::RenderWindow& window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;

    sf::Text titleText;
    std::vector<sf::Text> options;
    int selectedOption = 0;

public:
    MenuScreen(sf::RenderWindow& win);
    void draw();
    void handleInput(sf::Event event);
};
