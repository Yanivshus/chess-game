#include "Rook.h"

Rook::Rook(const Point& loc, const char color, const char type): Piece(loc, color, type)
{
}

Rook::~Rook()
{
}

bool Rook::checkIfChessKing() const
{
	return false;
}

int Rook::checkIfMoveValid() const
{
	return 0;
}
