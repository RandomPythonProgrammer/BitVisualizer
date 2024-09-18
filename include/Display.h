#pragma once
#include <SFML/Graphics.hpp>

class Display {
    private:
        uint64_t bits;
    public:
        Display();
        void toggleBits(uint64_t bits);
        void render(sf::RenderWindow* window);
};