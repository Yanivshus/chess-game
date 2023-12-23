#include "King.h"

King::King(const Point& loc, const char color, const char type) : Piece(loc, color, type)
{
}

King::~King()
{
}

int King::checkIfMoveValid(Board* board, const Point& dst) const
{
	return 0;
}

bool King::checkIfChessKing(Board* board, const Point& dest) const
{
	return false;
}
