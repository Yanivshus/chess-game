#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
Queen::Queen(const Point& loc, const char color, const char type):Piece(loc,color,type)
{
}

Queen::~Queen()
{
}

int Queen::checkIfMoveValid(Board* board, const Point& dst) const
{

    Rook sides(this->_loc, this->_color, this->_type);
    Bishop diagonal(this->_loc, this->_color, this->_type);

    // Check if the destination is reachable either diagonally or along rows/columns
    bool isValidMove = sides.checkIfMoveValid(board, dst) == VALID_MOVE ||
        diagonal.checkIfMoveValid(board, dst) == VALID_MOVE;

    if (!isValidMove) {
        return INVALID_MOVE_TOOL_MOVE_NOT_RIGHT;
    }

    return VALID_MOVE;
}

