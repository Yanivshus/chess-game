#include "Bishop.h"

Bishop::Bishop(const Point& loc, const char color, const char type):Piece(loc,color,type)
{
}

Bishop::~Bishop()
{
}

int Bishop::checkIfMoveValid(Board* board, const Point& dst) const
{
    int xPath = 0, yPath = 0;

    if (abs(this->_loc.getX() - dst.getX()) != abs(this->_loc.getY() - dst.getY())) {
        return INVALID_MOVE_TOOL_MOVE_NOT_RIGHT;
    }
    int xDiff = dst.getX() - this->_loc.getX();
    int yDiff = dst.getY() - this->_loc.getY();
    if (xDiff > 0) {
        xPath = 1;
    }
    else {
        xPath = -1;
    }
    if (yDiff > 0) {
        yPath = 1;
    }
    else {
        yPath = -1;
    }
    int i = this->_loc.getX() + xPath;
    int j = this->_loc.getY() + yPath;
    while (i != dst.getX()) {
        if (board->getPiece(Point(i, j))->getPieceType() != NULL_PIECE) {
            return INVALID_MOVE_TOOL_MOVE_NOT_RIGHT;
        }
        i += xPath;
        j += yPath;
    }
    return VALID_MOVE;
}
