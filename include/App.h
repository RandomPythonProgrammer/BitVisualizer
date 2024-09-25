#pragma once
#include "Display.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

enum class MODE {
    ADD,
    REMOVE
};

class App {
private:
    private:
        uint64_t bits;
        sf::RenderWindow* window;
        Display* display;
        MODE mode;
    public:
        App();
        ~App();
        void mainLoop();
        void updateSquares();
        void onClick();
        uint64_t getMouseSquare();
};