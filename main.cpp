#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "models/gamestate.hpp"
#include "models/homescreen.hpp"
#include "models/menuscreen.hpp"
#include "models/optionsscreen.hpp"
#include "models/game.hpp"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Volcanos VS Dinos");
    GameState state = GameState::HomeScreen;

    sf::Music backgroundMusic;

    if (!backgroundMusic.openFromFile("assets/jurassicpark.wav")) {
        std::cerr << "Erreur : impossible de charger la musique\n";
        return -1;
    }
    backgroundMusic.setLoop(true);
    backgroundMusic.setVolume(50.f);  // volume initial à 50%
    backgroundMusic.play();

    OptionsScreen options(window, backgroundMusic);

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
            else if (state == GameState::OptionsScreen) {
                auto result = options.handleInput(event);
                if (result.has_value()) {
                    state = GameState::MenuScreen;
                    // plus besoin de mettre à jour backgroundMusic ici
                }
            }
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
        else if (state == GameState::OptionsScreen) {
            options.draw();
        }

        window.display();
    }

    return 0;
}
