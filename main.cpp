#include <SFML/Graphics.hpp>
#include <optional>  // Nécessaire pour std::optional
#include <iostream>
#include "models/map.hpp"
#include "models/homescreen.hpp"
#include "models/menuscreen.hpp"
// #include "models/game.hpp" // Décommente si tu as une classe Game
#include "gamestate.hpp"

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

            if (state == GameState::HomeScreen) {
                GameState newState = home.handleEvents(event);
                if (newState != state)
                    state = newState;

            } else if (state == GameState::MenuScreen) {
                std::optional<GameState> selectedState = menu.handleInput(event);
                if (selectedState.has_value()) {
                    state = selectedState.value();
                    std::cout << "state = " << static_cast<int>(state) << std::endl;
                    // Ne pas appeler run_game() ici
                }

            } else if (state == GameState::Game) {
                // Si tu as besoin de gérer des events spécifiques au jeu, gère ici
            }
        }

        // Après la boucle d’événements, dans la partie affichage :
        window.clear();

        if (state == GameState::HomeScreen) {
            home.update();
            home.draw();

        } else if (state == GameState::MenuScreen) {
            menu.draw();

        } else if (state == GameState::Game) {
            run_game(); // Appelé ici à chaque frame
        }

        window.display();
    }

        return 0;
}
