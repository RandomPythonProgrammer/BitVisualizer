#pragma once
#include "Display.h"
#include <array>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <limits>

enum class MODE {
    ADD,
    REMOVE
};

namespace PieceType {
    enum Piece {
        KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, king, queen, bishop, knight, rook, pawn, BIT
    };
}

static std::array<std::string, 13> nameMap {
    "KING", "QUEEN", "BISHOP", "KNIGHT", "ROOK", "PAWN", "king", "queen", "bishop", "knight", "rook", "pawn", "BIT"
};

static std::map<sf::Keyboard::Key, PieceType::Piece> keymap{
    {sf::Keyboard::K, PieceType::Piece::KING},
    {sf::Keyboard::Q, PieceType::Piece::QUEEN},
    {sf::Keyboard::B, PieceType::Piece::BISHOP},
    {sf::Keyboard::N, PieceType::Piece::KNIGHT},
    {sf::Keyboard::R, PieceType::Piece::ROOK},
    {sf::Keyboard::P, PieceType::Piece::PAWN},
    {sf::Keyboard::Escape, PieceType::Piece::BIT}
};

class App {
    private:
        sf::RenderWindow* window;
        Display* display;
        MODE mode;
        PieceType::Piece piece;
        
    public:
        std::array<uint64_t, 13> bits;
        App();
        ~App();
        void mainLoop();
        void updateSquares();
        void onClick();
        uint64_t getMouseSquare();
        void switchLayer(PieceType::Piece layer);
        void load(std::filesystem::path path);
        void save(std::filesystem::path path);
        void clearOthers(uint64_t mask=std::numeric_limits<uint64_t>::max());
        uint64_t getEmpty();
};