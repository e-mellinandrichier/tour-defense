#include "dino.hpp"
#include "map.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 768), "Tower Defense");

    Map map;
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        map.update(deltaTime);

        window.clear();
        map.draw(window);
        window.display();
    }

    return 0;
}
