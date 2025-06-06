#include <SFML/Graphics.hpp>
#include "models/homescreen.hpp"
#include "models/menuscreen.hpp"
#include "GameState.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Volcanos VS Dinos");

    GameState state = GameState::HomeScreen;
    HomeScreen home(window);
    MenuScreen menu(window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (state == GameState::HomeScreen)
                state = home.handleEvents(event);
        }

        window.clear();

        if (state == GameState::HomeScreen) {
            home.update();
            home.draw();
        } else if (state == GameState::MenuScreen) {
            menu.draw();
        }

        window.display();
    }

    return 0;
}
