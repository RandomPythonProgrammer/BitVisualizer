#pragma once
#include "Display.h"
#include <array>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

enum class MODE {
    ADD,
    REMOVE
};

enum Piece {
    KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, king, queen, bishop, knight, rook, pawn, BIT
};

static std::array<std::string, 13> nameMap {
    "KING", "QUEEN", "BISHOP", "KNIGHT", "ROOK", "PAWN", "king", "queen", "bishop", "knight", "rook", "pawn", "BIT"
};

static std::map<sf::Keyboard::Key, Piece> keymap{
    {sf::Keyboard::K, Piece::KING},
    {sf::Keyboard::Q, Piece::QUEEN},
    {sf::Keyboard::B, Piece::BISHOP},
    {sf::Keyboard::N, Piece::KNIGHT},
    {sf::Keyboard::R, Piece::ROOK},
    {sf::Keyboard::P, Piece::PAWN},
    {sf::Keyboard::P, Piece::BIT}
};

class App {
private:
    private:
        std::array<uint64_t, 13> bits;
        sf::RenderWindow* window;
        Display* display;
        MODE mode;
        Piece piece;
        
    public:
        App();
        ~App();
        void mainLoop();
        void updateSquares();
        void onClick();
        uint64_t getMouseSquare();
        void switchLayer(Piece layer);
        void load(std::filesystem::path path);
        void save(std::filesystem::path path);
};