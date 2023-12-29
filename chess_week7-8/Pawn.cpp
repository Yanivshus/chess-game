#include "Pawn.h"

Pawn::Pawn(const Point& loc, const char color, const char type) : Piece(loc, color, type)
{
	this->_isFirst = TRUE;
}

Pawn::~Pawn()
{
}

int Pawn::checkIfMoveValid(Board* board, const Point& dst) const
{
	Piece*** gameBoard = board->getBoard();

	int srcX = this->_loc.getX();
	int srcY = this->_loc.getY();
	int dstX = dst.getX();
	int dstY = dst.getY();

	if (this->_color == WHITE_PLAYER_BOARD) {
		//checking if moving diognaly.
		if ((srcX + 1 == dstX && srcY + 1 == dstY) ||
			(srcX + 1 == dstX && srcY - 1 == dstY))
		{
			//checking if the piece in the dst is from different color.
			if (gameBoard[dstX][dstY]->getPieceColor() != NULL_PIECE &&
				gameBoard[dstX][dstY]->getPieceColor() != this->_color)//if yes that means we are capturing
			{
				return VALID_MOVE;
			}
			else
			{
				return INVALID_MOVE_TOOL_MOVE_NOT_RIGHT;
			}
		}
		else
		{
			if (this->_isFirst == TRUE)//if not moving diagnoly we check if this is the first move.
			{
				if (srcX + 2 == dstX && srcY == dstY)//if it is 1 squaere jump and 2 square jumps are allowed.
				{//checking if there are pieces in the way or in the dst.
					if (gameBoard[srcX + 1][srcY]->getPieceColor() == NULL_PIECE &&
						gameBoard[srcX + 2][srcY]->getPieceColor() == NULL_PIECE)
					{
						this->_isFirst = FALSE;
						return VALID_MOVE;
					}
					else
					{
						return INVALID_MOVE_TOOL_MOVE_NOT_RIGHT;
					}
				}
				else if (srcX + 1 == dstX && srcY == dstY)
				{//checking if there are pieces in the way or in the dst.
					if (gameBoard[srcX + 1][srcY]->getPieceColor() == NULL_PIECE)
					{
						return VALID_MOVE;
					}
					else
					{
						return INVALID_MOVE_TOOL_MOVE_NOT_RIGHT;
					}
				}
				else
				{
					return INVALID_MOVE_TOOL_MOVE_NOT_RIGHT;
				}
			}
			else
			{
				if (srcX + 1 == dstX && srcY == dstY)//if its not first move we will just check for 1 step.
				{
					if (gameBoard[dstX][dstY]->getPieceColor() == NULL_PIECE)//checking if there is a place to move to.
					{
						return VALID_MOVE;
					}
					else
					{
						return INVALID_MOVE_TOOL_MOVE_NOT_RIGHT;
					}
				}
				else
				{
					return INVALID_MOVE_TOOL_MOVE_NOT_RIGHT;
				}
			}
		}
	}
	else//if the player is black all the moves will be reveresed
	{
		//checking if moving diognaly.
		if ((srcX - 1 == dstX && srcY + 1 == dstY) ||
			(srcX - 1 == dstX && srcY - 1 == dstY))
		{
			//checking if the piece in the dst is from different color.
			if (gameBoard[dstX][dstY]->getPieceColor() != NULL_PIECE &&
				gameBoard[dstX][dstY]->getPieceColor() != this->_color)//if yes that means we are capturing
			{
				return VALID_MOVE;
			}
			else
			{
				return INVALID_MOVE_TOOL_MOVE_NOT_RIGHT;
			}
		}
		else
		{
			if (this->_isFirst == TRUE)//if not moving diagnoly we check if this is the first move.
			{
				if (srcX - 2 == dstX && srcY == dstY)//if it is 1 squaere jump and 2 square jumps are allowed.
				{//checking if there are pieces in the way or in the dst.
					if (gameBoard[srcX - 1][srcY]->getPieceColor() == NULL_PIECE &&
						gameBoard[srcX - 2][srcY]->getPieceColor() == NULL_PIECE)
					{
						this->_isFirst = FALSE;
						return VALID_MOVE;
					}
					else
					{
						return INVALID_MOVE_TOOL_MOVE_NOT_RIGHT;
					}
				}
				else if (srcX - 1 == dstX && srcY == dstY)
				{//checking if there are pieces in the way or in the dst.
					if (gameBoard[srcX - 1][srcY]->getPieceColor() == NULL_PIECE)
					{
						return VALID_MOVE;
					}
					else
					{
						return INVALID_MOVE_TOOL_MOVE_NOT_RIGHT;
					}
				}
				else
				{
					return INVALID_MOVE_TOOL_MOVE_NOT_RIGHT;
				}
			}
			else
			{
				if (srcX - 1 == dstX && srcY == dstY)//if its not first move we will just check for 1 step.
				{
					if (gameBoard[srcX - 1][srcY]->getPieceColor() == NULL_PIECE)//checking if there is a place to move to.
					{
						return VALID_MOVE;
					}
					else
					{
						return INVALID_MOVE_TOOL_MOVE_NOT_RIGHT;
					}
				}
				else
				{
					return INVALID_MOVE_TOOL_MOVE_NOT_RIGHT;
				}
			}
		}
	}
}

