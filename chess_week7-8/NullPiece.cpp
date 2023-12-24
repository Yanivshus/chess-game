#include "NullPiece.h"


NullPiece::NullPiece(const Point& loc, const char color, const char type) : Piece(loc, color, type)
{
}
//comment
NullPiece::~NullPiece()
{
}

int NullPiece::checkIfMoveValid(Board* board, const Point& dst) const
{
	return 0;
}

bool NullPiece::checkIfChessKing(Board* board, const Point& dest) const
{
	return false;
}
