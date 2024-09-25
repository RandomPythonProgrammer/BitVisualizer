#include "App.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Clipboard.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cstdint>
#include <iostream>
#include <limits>
#include <sstream>

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
                    std::stringstream string;
                    string << std::hex << bits;
                    sf::Clipboard::setString(string.str());
                } else if (event.key.code == sf::Keyboard::Key::Num1) {
                    bits = std::numeric_limits<uint64_t>::max();
                } else if (event.key.code == sf::Keyboard::Key::Num0) {
                    bits = std::numeric_limits<uint64_t>::min();
                } else if (event.key.code == sf::Keyboard::Key::Tilde) {
                    bits = ~bits;
                }
            }
        }
        updateSquares();
        display->render(window, bits);
    }
}

uint64_t App::getMouseSquare() {
    sf::Vector2i pos = sf::Mouse::getPosition(*window);
    int row = std::min(std::max(pos.y, 0), 800) / 100;
    int col = std::min(std::max(pos.x, 0), 800) / 100;
    return 1ULL << (63 - (row * 8 + col));
}

void App::onClick() {
    if (getMouseSquare() & bits) {
        mode = MODE::REMOVE;
    } else {
        mode = MODE::ADD;
    }
}

void App::updateSquares() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

        uint64_t toggle = getMouseSquare();

        if (((bits & toggle) && (mode == MODE::REMOVE)) || ((!(bits & toggle)) && (mode == MODE::ADD))) {
            bits ^= toggle;
        }
    }
}