#include "NullPiece.h"


NullPiece::NullPiece(const Point& loc, const char color, const char type) : Piece(loc, color, type)
{
}
NullPiece::~NullPiece()
{
}

int NullPiece::checkIfMoveValid(Board* board, const Point& dst) const
{
	return 3;
}


