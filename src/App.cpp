#include "App.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Clipboard.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>


App::App() {
    window = new sf::RenderWindow(sf::VideoMode(800, 800), "Visualizer");
    display = new Display(window);
    switchLayer(PieceType::Piece::BIT);
    bits.fill(0);
}

App::~App() {
    delete window;
    delete display;
}

void App::mainLoop() {
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed) {
                return;
            }
        }

        window->clear();
        display->drawBackground(bits[PieceType::Piece::BIT]);
        for (int i = 0; i < PieceType::Piece::BIT; i++) {
            display->drawLayer(bits[i], i);
        }
        display->drawText();
        window->display();
    }
}

uint64_t App::getMouseSquare() {
    sf::Vector2i pos = sf::Mouse::getPosition(*window);
    int row = std::min(std::max(pos.y, 0), 800) / 100;
    int col = std::min(std::max(pos.x, 0), 800) / 100;
    return 1ULL << (63 - (row * 8 + col));
}

void App::onClick() {
    if (getMouseSquare() & bits[piece]) {
        mode = MODE::REMOVE;
    } else {
        mode = MODE::ADD;
    }
}

void App::updateSquares() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

        uint64_t toggle = getMouseSquare();

        if (((bits[piece] & toggle) && (mode == MODE::REMOVE)) || ((!(bits[piece] & toggle)) && (mode == MODE::ADD))) {
            bits[piece] ^= toggle;
            if (piece != PieceType::Piece::BIT) {
                clearOthers(toggle);
            }
        }
    }
}

void App::switchLayer(PieceType::Piece layer) {
    piece = layer;
    display->setText(nameMap[piece]);
}

void App::save(std::filesystem::path path) {
    std::ofstream stream(path);
    if (stream.is_open()) {
        for (int i = 0; i < bits.size(); i++) {
            stream.write(reinterpret_cast<char*>(&bits[i]), sizeof(uint64_t));
        }
    }
}

void App::load(std::filesystem::path path) {
    std::ifstream stream(path);
    if (stream.is_open()) {
        for (int i = 0; i < bits.size(); i++) {
            stream.read(reinterpret_cast<char*>(&bits[i]), sizeof(uint64_t));
        }
    }
}

void App::clearOthers(uint64_t mask) {
    for (int i = PieceType::Piece::king; i < PieceType::Piece::BIT; i++) {
        if (i != piece) {
            bits[i] &= ~mask;
        }
    }
}

uint64_t App::getEmpty() {
    uint64_t mask = 0;
    for (int i = PieceType::Piece::king; i < PieceType::Piece::BIT; i++) {
        mask |= bits[i];
    }
    return ~mask;
}