#include "King.h"

King::King(const Point& loc, const char color, const char type) : Piece(loc, color, type)
{
}

King::~King()
{
}

int King::checkIfMoveValid(Board* board, const Point& dst) const
{
    //checking it the king moved to side diagnall or up by 1.
    bool validMoveKing = abs(this->_loc.getX() - dst.getX()) <= OFFSET && abs(this->_loc.getY()- dst.getY()) <= OFFSET;
    if (validMoveKing == true)//if moved right we will return correct code.
    {
        return VALID_MOVE;
    }
    else
    {
        return INVALID_MOVE_TOOL_MOVE_NOT_RIGHT;
    }
}
    