#include "Game.h"
#include "Queen.h"

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
			//if the move caused a chess on the currPlayer king we will undo the move and sent error code for chess out king
			if (checkForOwnPieceChess(this->_board) == INVALID_MOVE_CHESS_ON_CURRENT)
			{
				code = INVALID_MOVE_CHESS_ON_CURRENT;
				undoMove(src, dst);
			}
			else 
			{
				//checking if the piece is pawn, its color, and if in last row.
				if (this->_board->getPiece(dst)->getPieceType() == PAWN_WHITE &&
					this->_board->getPiece(dst)->getPieceLoc().getX() == ROWS - 1)
				{
					promotePawn(dst);
				}
				else if (this->_board->getPiece(dst)->getPieceType() == PAWN_BLACK &&
					this->_board->getPiece(dst)->getPieceLoc().getX() == ROW_SPOT)
				{
					promotePawn(dst);
				}
			}
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
	delete this->_pieceBefore;
	this->_pieceBefore = new NullPiece(Point(src.getX(), src.getY()), TYPE_NULL, TYPE_NULL);//creting the null piece for the before spot.

	//swapping the pieces
	swap(&board[dst.getX()][dst.getY()], &this->_pieceBefore);

	//for debugging
	std::cout << "" << std::endl;
	std::cout << this->_pieceBefore->getPieceType() << std::endl;
	std::cout << "" << std::endl;

	swap(&board[src.getX()][src.getY()], &board[dst.getX()][dst.getY()]);//now swapping.
	board[dst.getX()][dst.getY()]->setLoc(Point(dst.getX(), dst.getY()));
}


void Game::undoMove(const Point& src, const Point& dst)
{
	Piece*** board = this->_board->getBoard();

	swap(&board[src.getX()][src.getY()], &board[dst.getX()][dst.getY()]);//swapping the places of the dst and the src.

	std::cout << board[dst.getX()][dst.getY()]->getPieceType() << std::endl;//for debugging.
	std::cout << board[src.getX()][src.getY()]->getPieceType() << std::endl;

	swap(&board[dst.getX()][dst.getY()], &this->_pieceBefore);//replacing with piece before.

	
	std::cout << board[dst.getX()][dst.getY()]->getPieceType() << std::endl;//for debugging.
	std::cout << board[src.getX()][src.getY()]->getPieceType() << std::endl;

	//setting ne locations
	board[dst.getX()][dst.getY()]->setLoc(Point(dst.getX(), dst.getY()));
	board[src.getX()][src.getY()]->setLoc(Point(src.getX(), src.getY()));
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

void Game::promotePawn(Point pawnToPromote)
{
	Piece*** board = this->_board->getBoard();
	Piece* newQueen = nullptr;
	//checking the color fo the pawn
	//creating queen from the same color.
	if (board[pawnToPromote.getX()][pawnToPromote.getY()]->getPieceColor() == WHITE_PLAYER)
	{
		newQueen = new Queen(Point(pawnToPromote.getX(), pawnToPromote.getY()), WHITE_PLAYER, QUEEN_WHITE);
	}
	else{
		newQueen = new Queen(Point(pawnToPromote.getX(), pawnToPromote.getY()), BLACK_PLAYER, QUEEN_BLACK);
	}
	swap(&board[pawnToPromote.getX()][pawnToPromote.getY()], &newQueen);//switching the pawn to the queen.
	delete newQueen;//deleteing the pawn that was before.
}
