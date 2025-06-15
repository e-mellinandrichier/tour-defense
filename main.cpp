#include <SFML/Graphics.hpp>
#include "models/gamestate.hpp"
#include "models/homescreen.hpp"
#include "models/menuscreen.hpp"
#include "models/game.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Volcanos VS Dinos");
    GameState state = GameState::HomeScreen;

    HomeScreen home(window);
    MenuScreen menu(window);
    Game game(window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (state == GameState::HomeScreen)
                state = home.handleEvents(event);
            else if (state == GameState::MenuScreen) {
                auto result = menu.handleInput(event);
                if (result.has_value())
                    state = result.value();
            }
            else if (state == GameState::Game)
                game.handleEvents(event);
        }

        window.clear();

        if (state == GameState::HomeScreen) {
            home.update();
            home.draw();
        }
        else if (state == GameState::MenuScreen)
            menu.draw();
        else if (state == GameState::Game) {
            game.update();
            game.draw();
        }

        window.display();
    }

    return 0;
}
