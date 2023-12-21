#include "Game.h"

Game::Game()
{
	this->_board = new Board(STARTER_BOARD);
	this->_currPlayer = STARTER_BOARD[STARTER_PLAYER];
}

Game::~Game()
{
	delete this->_board;
}

std::string Game::turn(const std::string& playerMove)
{
	int code = 0, srcX = 0, srcY = 0, dstX = 0, dstY = 0;
	//checking if the move size is valid like e2e4.
	if (playerMove.size() == SIZE_OF_MOVE) {
		//turning each char of location to a number.
		srcY = playerMove[0] - OFFSET_Y;
		srcX = playerMove[1] - OFFSET_X;
		dstY = playerMove[2] - OFFSET_Y;
		dstX = playerMove[3] - OFFSET_X;
	}
	//creating points for src and dst.
	Point src(srcX, srcY);
	Point dst(dstX, dstY);
	//checking if there is somthing wrong with the points.
	code = checkIfTurnPossible(src, dst);
	//if nothing wrong we can proceed to move the player.
	if (code == VALID_MOVE)
	{
		Piece* srcPiece = this->_board->getPiece(src);
		code = srcPiece->checkIfMoveValid(this->_board, dst);
		if (code != VALID_MOVE) 
		{

		}
	}
	else
	{//if somthing were wrong with the specific move we will return the code.
		return std::to_string(code) + '\0';
	}


	//the turn changes after valid move, if move wasnt valid the turn stays on the current player.
	if (code == VALID_MOVE) {
		if (this->_currPlayer == WHITE_PLAYER) {
			this->_currPlayer = BLACK_PLAYER;
		}
		else {
			this->_currPlayer = WHITE_PLAYER;
		}
		return std::to_string(code) + '\0';
	}
	else {
		return std::to_string(code) + '\0';
	}
}

int Game::checkIfTurnPossible(const Point& src, const Point& dst) const
{
	//checking if y and x of the src and dst are between 0-7.
	if (src.getX() >= ROWS || src.getY() >= ROWS || dst.getX() >= ROWS || dst.getY() >= ROWS
		|| src.getX() < START_ARR || src.getY() < START_ARR || dst.getX() < START_ARR || dst.getY() < START_ARR)
	{
		return INVALID_MOVE_OUT_OF_INDEX;
	}
	else {
		//checking if the src and dst are the same.
		if (src.getX() == dst.getX() && src.getY() == dst.getX()) 
		{
			return INVALID_MOVE_SAME_SRC_DST;
		}
		else {
			//checking if the src piece is the same color as in the board.
			if (this->_board->getPiece(src)->getPieceColor() != this->_currPlayer)
			{
				return INVALID_MOVE_NO_TOOL_SRC;
			}
			else {
				//checking if there is current piece in the dst point on the board.
				if (this->_board->getPiece(dst)->getPieceColor() == this->_currPlayer) 
				{
					return INVALID_MOVE_TOOL_AT_DST;
				}
				else {
					return VALID_MOVE;
				}
			}
		}
	}
}

std::string Game::getBoardAsString() const
{
	return STARTER_BOARD;
}
