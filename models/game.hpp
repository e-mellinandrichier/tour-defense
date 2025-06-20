#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "map.hpp"
#include "dino.hpp"
#include "tour.hpp"

class Game {
public:
    Game(sf::RenderWindow& window);
    void handleEvents(sf::Event& event);
    void update();
    void draw();

private:
    sf::RenderWindow& window;
    std::vector<sf::Vector2i> path;
    std::vector<Dino*> dinos;
    std::vector<Tour> tours;

    sf::Clock clock;
    sf::Clock spawnClock;
    sf::Clock waveClock;

    int currentWave;
    int dinosToSpawn;
    float spawnInterval;
    bool waitingNextWave;

    sf::RectangleShape sidebar;
    sf::RectangleShape addTowerButton;
    bool placingTower;

    int playerMoney;
    int playerHealth;
    const int TOWER_COST = 50;

    sf::Font font;
    sf::Text moneyText;
    sf::Text healthLabelText;
    sf::Text healthValueText;

    void startNextWave();
    void updateMoneyText();
    void updateHealthText();
};

#endif
