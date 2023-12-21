#include "Board.h"

Board::Board(const std::string& board)
{
	char boardAsString[ROWS][COLS] = { 0 };
	//looping through the board as a long string and coverting it to 2d array. 
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			boardAsString[i][j] = board[i * COLS + j];
		}
	}

	this->_board = new Piece**[ROWS];
	for (int k = 0; k < ROWS; k++)
	{
		_board[k] = new Piece*[ROWS]; //intalizing the array
	}

	for (int q = 0; q < ROWS; q++)
	{
		for (int m = 0; m < COLS; m++)
		{
			char currPiece = boardAsString[q][m];
			switch (currPiece)
			{
			case KING_BLACK:
				break;
			case ROOK_BLACK:
				break;
			case PAWN_BLACK:
				break;
			case KNIGHT_BLACK:
				break;
			case BISHOP_BLACK:
				break;
			case QUEEN_BLACK:
				break;
			case KING_WHITE:
				break;
			case ROOK_WHITE:
				break;
			case PAWN_WHITE:
				break;
			case KNIGHT_WHITE:
				break;
			case BISHOP_WHITE:
				break;
			case QUEEN_WHITE:
				break;
			case NULL_PIECE:
				break;
			}
		}
	}
}

Board::~Board()
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (this->_board[i][j] != nullptr)
			{
				delete this->_board[i][j]; //deleting each ChessPiece
			}
		}

		delete[] this->_board[i]; //deleting the entire row
	}

	delete[] this->_board; //deleting the entire board
}

Piece*** Board::getBoard() const
{
	return this->_board;
}

Piece* Board::getPiece(Point src) const
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			if (src.getX() == this->_board[i][j]->getPieceLoc().getX()
				&& src.getY() == this->_board[i][j]->getPieceLoc().getY())
			{
				return this->_board[i][j];
			}
		}
	}
	return nullptr;
}
