#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "models/gamestate.hpp"
#include "models/homescreen.hpp"
#include "models/menuscreen.hpp"
#include "models/optionsscreen.hpp"
#include "models/creditscreen.hpp"
#include "models/game.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Volcanos VS Dinos");
    GameState state = GameState::HomeScreen;

    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("assets/jurassicpark.wav")) {
        std::cerr << "Erreur : impossible de charger la musique\n";
        return -1;
    }
    backgroundMusic.setLoop(true);
    backgroundMusic.setVolume(50.f); // volume initial
    backgroundMusic.play();

    // Écrans
    HomeScreen home(window);
    MenuScreen menu(window);
    OptionsScreen options(window, backgroundMusic);
    CreditScreen credits(window);
    Game game(window);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Gestion des inputs selon l’état
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
                if (result.has_value())
                    state = GameState::MenuScreen;
            }
            else if (state == GameState::CreditScreen) {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    state = GameState::HomeScreen;
                }
            }
        }

        float dt = clock.restart().asSeconds();

        // Rendu
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
        else if (state == GameState::OptionsScreen)
            options.draw();
        else if (state == GameState::CreditScreen) {
            credits.update(dt);
            credits.draw();
            if (credits.isFinished())
                state = GameState::HomeScreen;
        }

        window.display();
    }

    return 0;
}
