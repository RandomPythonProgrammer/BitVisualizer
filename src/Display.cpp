#include "Display.h"
#include "SpriteSheet.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <filesystem>

Display::Display(sf::RenderTarget* target) {
    this->target = target;
    std::filesystem::path path = std::filesystem::current_path();
    path = path / "assets";
    loader = new SpriteSheet(path / "pieces.bmp", 2, 6);
    bits = 0;
    font.loadFromFile(path / "OpenSans-Regular.ttf");
}

Display::~Display() {
    delete loader;
}

void Display::drawBackground(uint64_t bits) {
    for (int i = 0; i < 8; i++) {
        for (int ii = 0; ii < 8; ii++) {
            uint64_t mask = 1ULL << (63 - (i * 8 + ii));
            sf::Color color = (bits & mask) ? sf::Color::Red: sf::Color::White;
            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(100 ,100));
            rect.setPosition(sf::Vector2f(ii * 100, i * 100));
            rect.setFillColor(color);
            rect.setOutlineColor(sf::Color::Black);
            rect.setOutlineThickness(2);
            target->draw(rect);
        }
    }

}

void Display::drawLayer(uint64_t bits, int index) {
    for (int i = 0; i < 8; i++) {
        for (int ii = 0; ii < 8; ii++) {
            uint64_t mask = 1ULL << (63 - (i * 8 + ii));

            if (mask & bits) {
                sf::Sprite sprite = loader->getSprite(index);
                int width = sprite.getTextureRect().height;
                int height = sprite.getTextureRect().width;
                sprite.setScale(sf::Vector2f(1e2/height,1e2/width));
                sprite.setPosition(sf::Vector2f(ii * 100, i * 100));
                target->draw(sprite);
            }
        }
    }
}

void Display::setText(std::string text) {
    this->text = text;
}

void Display::drawText() {
    sf::Text label;
    label.setString(text);
    label.setFont(font);
    label.setFillColor(sf::Color::Black);
    label.setCharacterSize(50);
    label.setPosition(0, 0);
    target->draw(label);
}