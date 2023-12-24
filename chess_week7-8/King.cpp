#include "King.h"

King::King(const Point& loc, const char color, const char type) : Piece(loc, color, type)
{
}

King::~King()
{
}

int King::checkIfMoveValid(Board* board, const Point& dst) const
{
    bool validMoveKing = abs(this->_loc.getX() - dst.getX()) <= OFFSET && abs(this->_loc.getY()- dst.getY()) <= OFFSET;
    if (validMoveKing)
    {
        return VALID_MOVE;
    }
    return INVALID_MOVE_TOOL_MOVE_NOT_RIGHT;
}


bool King::checkIfChessKing(Board* board, const Point& dest) const
{
	return false;
}
