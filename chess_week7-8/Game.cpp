#include "Game.h"
//#include "King.h"
#include <exception>

Game::Game()
{
	this->_pieceBefore = nullptr;
	this->_board = new Board(STARTER_BOARD);
	this->_currPlayer = STARTER_BOARD[STARTER_PLAYER];
}

Game::~Game()
{
	delete this->_board;
	delete this->_pieceBefore;
}

std::string Game::turn(const std::string& playerMove)
{
	int code = 0, srcX = 0, srcY = 0, dstX = 0, dstY = 0;
	//checking if the move size is valid like e2e4.
	if (playerMove.size() == SIZE_OF_MOVE) {
		//turning each char of location to a number.
		srcY = playerMove[0] - OFFSET_Y;
		srcX = playerMove[1] - OFFSET_X - X_NULLER_OFFSET;
		dstY = playerMove[2] - OFFSET_Y;
		dstX = playerMove[3] - OFFSET_X - X_NULLER_OFFSET;
	}
	else {
		return std::to_string(INVALID_MOVE_OUT_OF_INDEX) + '\0';
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
		if (code == VALID_MOVE) 
		{
			movePiece(src, dst);
			Piece* newPlacePiece = this->_board->getPiece(dst);
			//checking if the piece after i moved it and checked if it moved right , made chess on the op king.
			if (checkForChessOnOp(this->_board, newPlacePiece) == VALID_MOVE_CHESS)
			{
				code = VALID_MOVE_CHESS;//if yes the code will be chess.
			}
			else 
			{
				code = VALID_MOVE;//if not the code will remain valid move.
			}
			
		}
		//if the move caused a chess on the currPlayer king we will undo the move and sent error code for chess out king
		if (checkForOwnPieceChess(this->_board) == INVALID_MOVE_CHESS_ON_CURRENT)
		{
			code = INVALID_MOVE_CHESS_ON_CURRENT;
			undoMove(dst, src);
		}
		else
		{//if there wasn't an undo needed i will delete the piece i saved.
			//delete this->_pieceBefore;
			//this->_pieceBefore = nullptr;
		}
		//just for debugging
		std::cout << getBoardAsString() << std::endl;
		std::cout << this->_currPlayer << std::endl;
		//just for debugging
	}
	else
	{//if somthing were wrong with the specific move we will return the code.
		return std::to_string(code) + '\0';
	}


	//the turn changes after valid move, if move wasnt valid the turn stays on the current player.
	if (code == VALID_MOVE || code == VALID_MOVE_CHESS) {
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
		if (src.getX() == dst.getX() && src.getY() == dst.getY()) 
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
	std::string boardString = "";
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			boardString += this->_board->getPiece(Point(i, j))->getPieceType();
			boardString += this->_board->getPiece(Point(i, j))->getPieceColor();
			boardString += " ";
		}
		boardString += "\n";
	}
	return boardString;
}





void Game::movePiece(const Point& src, const Point& dst)
{
	
	Piece*** board = this->_board->getBoard();

	this->_pieceBefore = board[dst.getX()][dst.getY()];


	board[dst.getX()][dst.getY()] = new NullPiece(Point(src.getX(), src.getY()), TYPE_NULL, TYPE_NULL);
	swap(&board[src.getX()][src.getY()], &board[dst.getX()][dst.getY()]);
	board[dst.getX()][dst.getY()]->setLoc(Point(dst.getX(), dst.getY()));
}


void Game::undoMove(const Point& src, const Point& dst)
{
	Piece*** board = this->_board->getBoard();

	swap(&board[dst.getX()][dst.getY()], &board[src.getX()][src.getY()]);

	std::cout << board[dst.getX()][dst.getY()]->getPieceType() << std::endl;
	std::cout << board[src.getX()][src.getY()]->getPieceType() << std::endl;

	swap(&board[dst.getX()][dst.getY()], &this->_pieceBefore);//the error is here in the swap.
	//for some reason a player is dissapereanig.
	std::cout << board[dst.getX()][dst.getY()]->getPieceType() << std::endl;
	std::cout << board[src.getX()][src.getY()]->getPieceType() << std::endl;
	//in the chack you can see R # # # and not R # R # like it should.

	
	delete this->_pieceBefore;
	this->_pieceBefore = nullptr;

	//*board[dst.getX()][dst.getY()] = *board[src.getX()][src.getY()];
	//*board[src.getX()][src.getY()] = *this->_pieceBefore;

	board[dst.getX()][dst.getY()]->setLoc(Point(src.getX(), src.getY()));
	//std::cout << board[dst.getX()][dst.getY()]->getPieceType() << std::endl;
	board[src.getX()][src.getY()]->setLoc(Point(dst.getX(), dst.getY()));
	//std::cout << board[src.getX()][src.getY()]->getPieceType() << std::endl;
}


int Game::checkForOwnPieceChess(Board* board) const
{
	Piece*** gameBoard = this->_board->getBoard();

	//checking if the player is white.
	//if yes i will find the king location on the board.
	if (this->_currPlayer == WHITE_PLAYER) 
	{
		Point whiteKingLoc = board->getKingWhiteLoc();
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS; j++)
			{//after i found the pieces from the other player i will pass them the king loction.
				if(gameBoard[i][j]->getPieceColor() != WHITE_PLAYER &&
					gameBoard[i][j]->getPieceType() != TYPE_NULL)
				{//if the op player piece can it my king it meanes chess was made.
					if (gameBoard[i][j]->checkIfMoveValid(board, whiteKingLoc) == VALID_MOVE)
					{
						return INVALID_MOVE_CHESS_ON_CURRENT;
					}
				}
			}
		}
	}
	else 
	{//if the player is not white we will do all the process mentioned before all over again but switching the colors.
		Point blackKing = board->getKingBlackLoc();
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS; j++)
			{
				if (gameBoard[i][j]->getPieceColor() == WHITE_PLAYER &&
					gameBoard[i][j]->getPieceType() != TYPE_NULL)
				{
					if (gameBoard[i][j]->checkIfMoveValid(board, blackKing) == VALID_MOVE)
					{
						return INVALID_MOVE_CHESS_ON_CURRENT;
					}
				}
			}
		}
	}
	return VALID_MOVE;
}

int Game::checkForChessOnOp(Board* board, Piece* toCheck)
{
	// if the current player playing is white we will check if he is treatening the black king.
	if (this->_currPlayer == WHITE_PLAYER) {
		Point kingBlack = board->getKingBlackLoc();
		if (toCheck->checkIfMoveValid(board, kingBlack) == VALID_MOVE)
		{
			return VALID_MOVE_CHESS;
		}
		else {
			return VALID_MOVE;
		}
	}
	else // if the current player playing is black we will check if he is treatening the white king.
	{
		Point kingWhite = board->getKingWhiteLoc();
		if (toCheck->checkIfMoveValid(board, kingWhite) == VALID_MOVE)
		{
			return VALID_MOVE_CHESS;
		}
		else
		{
			return VALID_MOVE;
		}
	}	
}

void Game::swap(Piece** src, Piece** dst)
{
	Piece* tmp = *src;
	*src = *dst;
	*dst = tmp;
}
