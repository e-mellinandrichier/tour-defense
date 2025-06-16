#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class CreditScreen {
public:
    CreditScreen(sf::RenderWindow& window);
    void update(float dt);
    void draw();
    bool isFinished() const;

private:
    sf::RenderWindow& window;
    sf::Font font;
    std::vector<sf::Text> credits;
    float scrollSpeed;
};
