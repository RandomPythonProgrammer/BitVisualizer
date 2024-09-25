#include "Display.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>

Display::Display() {
    bits = 0;
}

void Display::render(sf::RenderWindow* window, uint64_t bits) {
    window->clear();
    for (int i = 0; i < 8; i++) {
        for (int ii = 0; ii < 8; ii++) {
            uint64_t mask = 1ULL << (63 - (i * 8 + ii));
            sf::Color color = sf::Color::White;
            if (mask & bits) {
                color = sf::Color::Red;
            }
            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(100 ,100));
            rect.setPosition(sf::Vector2f(ii * 100, i * 100));
            rect.setFillColor(color);
            rect.setOutlineColor(sf::Color::Black);
            rect.setOutlineThickness(2);
            window->draw(rect);;
        }
    }
    window->display();
}