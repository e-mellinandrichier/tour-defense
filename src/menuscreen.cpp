#include "../models/menuscreen.hpp"
#include "../models/buttonfactory.hpp"

MenuScreen::MenuScreen(sf::RenderWindow& win) : window(win) {
    backgroundTexture.loadFromFile("assets/menubg.jpg");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        (float)window.getSize().x / backgroundTexture.getSize().x,
        (float)window.getSize().y / backgroundTexture.getSize().y
    );

    font.loadFromFile("assets/Pixelcraft.ttf");

    titleText.setFont(font);
    titleText.setString("MENU");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color::Red);
    sf::FloatRect bounds = titleText.getLocalBounds();
    titleText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    titleText.setPosition(window.getSize().x / 2.f, window.getSize().y / 6.f);

    buttons = ButtonFactory::createMenuButtons(font, window.getSize());
    buttons[selectedOption].setSelected(true);
}

void MenuScreen::draw() {
    window.draw(backgroundSprite);
    window.draw(titleText);
    for (const auto& btn : buttons)
        btn.draw(window);
}

std::optional<GameState> MenuScreen::handleInput(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        buttons[selectedOption].setSelected(false);
        if (event.key.code == sf::Keyboard::Up && selectedOption > 0)
            selectedOption--;
        else if (event.key.code == sf::Keyboard::Down && selectedOption < (int)buttons.size() - 1)
            selectedOption++;
        buttons[selectedOption].setSelected(true);

        if (event.key.code == sf::Keyboard::Space)
            return getSelectedState();
    }
    return std::nullopt;
}

std::optional<GameState> MenuScreen::getSelectedState() const {
    std::string label = buttons[selectedOption].getLabel();
    if (label == "Play") return GameState::Game;
    if (label == "Options") return GameState::OptionsScreen;
    if (label == "Credits") return GameState::CreditScreen;
    return std::nullopt;
}
