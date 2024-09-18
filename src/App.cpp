#include "App.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>

App::App() {
    window = new sf::RenderWindow(sf::VideoMode(800, 800), "Visualizer");
    display = new Display();
    bits = 0;
}

App::~App() {
    delete window;
    delete display;
}

void App::mainLoop() {
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::EventType::MouseButtonPressed) {
                onClick();
            } else if (event.type == sf::Event::EventType::Closed) {
                return;
            } else if (event.type == sf::Event::EventType::KeyPressed) {
                if (event.key.code == sf::Keyboard::Key::Enter) {
                    std::cout << "Decimal: " << std::dec << bits << std::endl;
                    std::cout << "Hex: " << std::hex << bits << std::endl;
                    std::cout << std::endl;
                }
            }
        }
        display->render(window);
    }
}

void App::onClick() {
    sf::Vector2i pos = sf::Mouse::getPosition(*window);
    int row = pos.y / 100;
    int col = pos.x / 100;
    uint64_t toggle = 1ULL << (63 - (row * 8 + col));
    bits ^= toggle;
    display->toggleBits(toggle);
}