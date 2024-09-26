#pragma once
#include "SpriteSheet.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Display {
    private:
        uint64_t bits;
        SpriteSheet* loader;
        sf::RenderTarget* target;
        std::string text;
        sf::Font font;
    public:
        Display(sf::RenderTarget* target);
        ~Display();
        void drawBackground(uint64_t bits);
        void drawLayer(uint64_t bits, int index);
        void drawText();
        void setText(std::string text);
};

sf::Sprite loadSprite(int index);