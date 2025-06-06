#include <SFML/Graphics.hpp>
#include "models/homescreen.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Transition vers menu");

    GameState state = GameState::Intro;
    HomeScreen home(window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            home.handleEvent(event, state);
        }

        home.update(state);

        window.clear();
        home.draw(window, state);
        window.display();
    }

    return 0;
}
