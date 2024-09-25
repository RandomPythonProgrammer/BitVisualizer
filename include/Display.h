#pragma once
#include <SFML/Graphics.hpp>

class Display {
    private:
        uint64_t bits;
    public:
        Display();
        void render(sf::RenderWindow* window, uint64_t bits);
};