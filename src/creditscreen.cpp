#include "../models/creditscreen.hpp"
#include <iostream>

CreditScreen::CreditScreen(sf::RenderWindow& win) : window(win), scrollSpeed(50.0f) {
    if (!font.loadFromFile("assets/Pixelcraft.ttf")) {
        std::cerr << "Erreur de chargement de la police\n";
    }

    std::vector<std::string> lines = {
        "Credits",
        "",
        "Un projet de  Yoel",
        "LEAD MANAGER Yoel",
        "Interface designer Yoel",
        "Direction artistique Yoel",
        "Senior Programmer Yoel",
        "Musique Yoel",
        "Volcan Yoel",
        "Dino Yoel",
        "Financement Yoel",
        "Conceptualisation Yoel",
        "Cafe frappe Yoel",
        "Compilateur Yoel",
        "Menage Yoel",
        "Vaisselle Yoel",
        "Robot Yoel",
        "Cuisine Yoel",
        "Chemin Yoel",
        "President de la republique Yoel",
        "Inventeur de SFML Yoel",
        "2025 - Volcanos VS Dinos"
    };

    float startY = window.getSize().y;
    for (size_t i = 0; i < lines.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(lines[i]);
        text.setCharacterSize(28);
        text.setFillColor(sf::Color::White);
        text.setPosition(100, startY + i * 50);
        credits.push_back(text);
    }
}

void CreditScreen::update(float dt) {
    for (auto& text : credits) {
        text.move(0, -scrollSpeed * dt);  // défilement vers le haut
    }
}

void CreditScreen::draw() {
    for (auto& text : credits) {
        window.draw(text);
    }
}

bool CreditScreen::isFinished() const {
    return credits.back().getPosition().y + 50 < 0;
}
