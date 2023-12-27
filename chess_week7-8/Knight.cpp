#include "Knight.h"

Knight::Knight(const Point& loc, const char color, const char type) : Piece(loc, color, type)
{
}

Knight::~Knight()
{
}

int Knight::checkIfMoveValid(Board* board, const Point& dst) const
{
	//saving the dst and src as locals.
	int srcX = this->_loc.getX();
	int srcY = this->_loc.getY();
	int dstX = dst.getX();
	int dstY = dst.getY();

	// #x#x#
	// x###x
	// ##K##
	// x###x
	// #x#x#
	//all knight pssibilities.
	if ((srcX + 2 == dstX && srcY - 1 == dstY) || 
		(srcX + 1 == dstX && srcY - 2 == dstY) ||
		(srcX - 1 == dstX && srcY - 2 == dstY) ||
		(srcX - 2 == dstX && srcY - 1 == dstY) || // done the left side possibilities.
		(srcX + 2 == dstX && srcY + 1 == dstY) ||
		(srcX + 1 == dstX && srcY + 2 == dstY) ||
		(srcX - 1 == dstX && srcY + 2 == dstY) ||
		(srcX - 2 == dstX && srcY + 1 == dstY)) // done the right side possibilities.
	{
		return VALID_MOVE;
	}
	else
	{
		return INVALID_MOVE_TOOL_MOVE_NOT_RIGHT;
	}
}
