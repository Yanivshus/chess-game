#include "Game.h"
//#include "King.h"

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
		srcX = playerMove[1] - OFFSET_X - 1;
		dstY = playerMove[2] - OFFSET_Y;
		dstX = playerMove[3] - OFFSET_X - 1;
	}
	//creating points for src and dst.
	Point src(srcX, srcY);
	Point dst(dstX, dstY);

	//just for debugging
	std::cout << getBoardAsString() << std::endl;
	std::cout << this->_currPlayer << std::endl;
	//just fro debugging

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
			std::cout << "here1" << std::endl;
			return INVALID_MOVE_SAME_SRC_DST;
		}
		else {
			//checking if the src piece is the same color as in the board.
			if (this->_board->getPiece(src)->getPieceColor() != this->_currPlayer)
			{
				std::cout << "here2" << std::endl;
				return INVALID_MOVE_NO_TOOL_SRC;
			}
			else {
				//checking if there is current piece in the dst point on the board.
				if (this->_board->getPiece(dst)->getPieceColor() == this->_currPlayer) 
				{
					std::cout << "here3" << std::endl;
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
	Piece* pieceToMove = this->_board->getPiece(src);
	Piece* pieceInTheDest = this->_board->getPiece(dst);
	Piece*** board = this->_board->getBoard();

	//the loop will find the piece we want to move,
	//puts a null piece instead of it because we moved it
	//and then finds dst and deletes the piece in the dest and place the source piece there.

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			//check for source
			if(board[i][j]->getPieceLoc().getX() == src.getX() &&
				board[i][j]->getPieceLoc().getY() == src.getY())
			{
				board[i][j] = new NullPiece(Point(i, j), TYPE_NULL, TYPE_NULL);

			}

		}
	}
	for (int m = 0; m < ROWS; m++)
	{
		for (int q = 0; q < COLS; q++)
		{
			//check for dst
			if (board[m][q]->getPieceLoc().getX() == dst.getX() &&
				board[m][q]->getPieceLoc().getY() == dst.getY())
			{
				//checking if the piece from previous moves i saved was deleted if not we will delete it.
				delete this->_pieceBefore;
				this->_pieceBefore = board[m][q];
				board[m][q] = pieceToMove;
				board[m][q]->setLoc(Point(m, q));
			}
		}
	}
}

void Game::undoMove(const Point& src, const Point& dst)
{
	//not sure about this function.
	Piece*** board = this->_board->getBoard();
	Piece* toPlace = nullptr;

	//in the first loop i will find the tool i want to undo his move
	//then i will save the tool there i that place for later and put there the tool that was before.
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (board[i][j]->getPieceLoc().getX() == src.getX() &&
				board[i][j]->getPieceLoc().getY() == src.getY())
			{
				toPlace = board[i][j];
				board[i][j] = this->_pieceBefore;
			}
		}
	}
	//in the second loop i will find the dst of the undo
	//after i found it i will delete what was there before which is a nullPiece
	//and place the tool i undoed his move back to his original place and sets his point back to original.
	for (int m = 0; m < ROWS; m++)
	{
		for (int q = 0; q < COLS; q++)
		{

			if (board[m][q]->getPieceLoc().getX() == dst.getX() &&
				board[m][q]->getPieceLoc().getY() == dst.getY())
			{
				delete board[m][q];
				board[m][q] = toPlace;
				board[m][q]->setLoc(Point(m, q));
			}

		}
	}

}

int Game::checkForOwnPieceChess(Board* board) const
{
	Piece*** gameBoard = this->_board->getBoard();

	if (this->_currPlayer == WHITE_PLAYER) 
	{
		Point whiteKingLoc = board->getKingWhiteLoc();
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS; j++)
			{
				if(gameBoard[i][j]->getPieceColor() != WHITE_PLAYER &&
					gameBoard[i][j]->getPieceType() != TYPE_NULL)
				{
					if (gameBoard[i][j]->checkIfMoveValid(board, whiteKingLoc) == VALID_MOVE)
					{
						return INVALID_MOVE_CHESS_ON_CURRENT;
					}
				}
			}
		}
	}
	else 
	{
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
		else{
			return VALID_MOVE;
		}
	}	
}