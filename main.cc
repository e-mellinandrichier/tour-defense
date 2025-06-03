#include <SFML/Graphics.hpp>
#include <vector>

const int TILE_SIZE = 64;
const int MAP_WIDTH = 10;
const int MAP_HEIGHT = 10;

enum TileType {
    EMPTY,
    PATH,
    START,
    END
};

// Une map simple avec un chemin prédéfini
int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0},
    {0,0,0,0,1,2,0,0,0,0},
    {0,0,0,0,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,1,1,1,1},
    {0,0,0,0,0,2,1,0,0,0},
    {0,0,0,0,0,0,1,0,0,0},
    {0,0,0,0,0,0,1,0,0,0}
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE), "Tower Defense");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // Dessin de la grille
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            for (int x = 0; x < MAP_WIDTH; ++x) {
                sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);

                if (map[y][x] == PATH) {
                    tile.setFillColor(sf::Color(200, 200, 0)); // Jaune pour le chemin
                } else if (map[y][x] == EMPTY) {
                    tile.setFillColor(sf::Color(100, 100, 100)); // Gris pour terrain vide
                } else {
                    tile.setFillColor(sf::Color(255, 0, 0)); // Rouge pour les tours
                }

                tile.setOutlineThickness(2);
                tile.setOutlineThickness(1);
                tile.setOutlineColor(sf::Color::Black);
                window.draw(tile);
            }
        }

        window.display();
    }

    return 0;
}
