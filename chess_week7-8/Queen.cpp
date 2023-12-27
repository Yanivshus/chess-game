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
	Rook sides(this->_loc, this->_color,this->_type);
	Bishop diagnoal(this->_loc, this->_color, this->_type);
	if (sides.checkIfMoveValid(board, dst) == INVALID_MOVE_TOOL_MOVE_NOT_RIGHT|| 
		diagnoal.checkIfMoveValid(board, dst)== INVALID_MOVE_TOOL_MOVE_NOT_RIGHT) {
		return INVALID_MOVE_TOOL_MOVE_NOT_RIGHT;
	}
	return VALID_MOVE;

}
