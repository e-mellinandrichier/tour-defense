#include "models/game.hpp"

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

            // Gestion par état
            if (state == GameState::HomeScreen) {
                GameState newState = home.handleEvents(event);
                if (newState != state)
                    state = newState;
            } else if (state == GameState::MenuScreen) {
                menu.handleInput(event);
            }
        }

        window.clear();

        // Affichage par état
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
