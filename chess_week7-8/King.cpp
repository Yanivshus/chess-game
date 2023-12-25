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
    if (validMoveKing == true)
    {
        return VALID_MOVE;
    }
    else
    {
        return INVALID_MOVE_TOOL_MOVE_NOT_RIGHT;
    }
}
    