#include "SpriteSheet.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

SpriteSheet::SpriteSheet(std::filesystem::path path, int rows, int cols) {
    this->rows = rows;
    this->cols = cols;
    texture.loadFromFile(path);
}

sf::Sprite SpriteSheet::getSprite(int index) {
    sf::Sprite sprite;

    int row = index / cols;
    int col = index % cols;
    int width = texture.getSize().x/cols;
    int height = texture.getSize().y/rows;

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(
        col * width,
        row * height,
        width,
        height
    ));

    return sprite;
}