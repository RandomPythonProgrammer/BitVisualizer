#pragma once
#include "Display.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class App {
private:
    private:
        uint64_t bits;
        sf::RenderWindow* window;
        Display* display;
    public:
        App();
        ~App();
        void mainLoop();
        void onClick();
};