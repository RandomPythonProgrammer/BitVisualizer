#include "App.h"
#include "board.h"

int main()
{
    App app;
    app.bits[PieceType::Piece::bishop] = 1ULL << 10;
    app.bits[PieceType::Piece::BIT] = calculateBishopAttacks(10, 0);
    app.mainLoop();
}
