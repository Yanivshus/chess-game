#include "Board.h"

Board::Board(const std::string& board)
{
	setBoard(board);
}

Board::~Board()
{
	//deleting all allocated pieces.
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++) 
		{
			delete this->_board[i][j];
		}
	}
}

void Board::setBoard(const std::string& board)
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
	
	//creating a piece for each spot;
	for (int q = 0; q < ROWS; q++)
	{
		for (int k = 0; k < COLS; k++)
		{
			char currPiece = boardAsString[q][k];
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
}

Point Board::destructLocation(const std::string& loc) const
{
	return Point();
}
