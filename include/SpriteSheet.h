#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <filesystem>

class SpriteSheet {
private:
    sf::Texture texture;
    int rows, cols;
public:
    SpriteSheet(std::filesystem::path path, int rows, int cols);
    sf::Sprite getSprite(int index);
};