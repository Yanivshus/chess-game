#include "Rook.h"

Rook::Rook(const Point& loc, const char color, const char type) : Piece(loc, color, type)
{
}

Rook::~Rook()
{
}

int Rook::checkIfMoveValid(Board* board, const Point& dst) const
{
    int i = 0;
    // Collision detection
    if (this->_loc.getX() == dst.getX()) {
        // Horizontal move
        if (this->_loc.getY() < dst.getY()) {
            // Move right
            for (i = this->_loc.getY() + 1; i <= dst.getY(); ++i)
                if (board->getPiece(Point(this->_loc.getX(), i))->getPieceType() != NULL_PIECE)
                    return INVALID_MOVE_TOOL_MOVE_NOT_RIGHT;
        }
        else {
            // Move left
            for (i = this->_loc.getY() - 1; i >= dst.getY(); --i)
                if (board->getPiece(Point(this->_loc.getX(), i))->getPieceType() != NULL_PIECE)
                    return INVALID_MOVE_TOOL_MOVE_NOT_RIGHT;
        }
    }
    else if (this->_loc.getY() == dst.getY()) {
        // Vertical move
        if (this->_loc.getX() < dst.getX()) {
            // Move down
            for (i = this->_loc.getX() + 1; i <= dst.getX(); ++i)
                if (board->getPiece(Point(this->_loc.getY(), i))->getPieceType() != NULL_PIECE)
                    return INVALID_MOVE_TOOL_MOVE_NOT_RIGHT;
        }
        else {
            // Move up
            for (i = this->_loc.getX() - 1; i >= dst.getX(); --i)
                if (board->getPiece(Point(this->_loc.getY(), i))->getPieceType() != NULL_PIECE)
                    return INVALID_MOVE_TOOL_MOVE_NOT_RIGHT;
        }
    }
    else {
        // Not a valid rook move (neither horizontal nor vertical)
        return INVALID_MOVE_TOOL_MOVE_NOT_RIGHT;
    }

    return VALID_MOVE;
}

bool Rook::checkIfChessKing(Board* board, const Point& dst) const
{
	return false;
}

