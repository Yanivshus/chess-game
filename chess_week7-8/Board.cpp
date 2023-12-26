#include "Board.h"
#include "NullPiece.h"
#include "King.h"
#include "Rook.h"
#include <string>

Board::Board(const std::string& board)
{
	//try branches
	//problemmmmmmmmmmmm
	char boardAsString[ROWS][COLS] = { 0 };
	//looping through the board as a long string and coverting it to 2d array. 
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			boardAsString[i][j] = board[i * COLS + j];
		}
	}
	//looping throgh the board and allocating space for each piece.
	this->_board = new Piece**[ROWS];
	for (int k = 0; k < ROWS; k++)
	{
		_board[k] = new Piece*[COLS]; //intalizing the array
	}

	//looping another time on the board.
	for (int q = 0; q < ROWS; q++)
	{
		for (int m = 0; m < COLS; m++)
		{
			//getting the location from the board 2d array of chars and creting by the char the current piece.
			char currPiece = boardAsString[q][m];
			switch (currPiece)//allocting memmory by the type.
			{
			case KING_BLACK:
				this->_board[q][m] = new King(Point(q, m), BLACK_PLAYER_BOARD,KING_BLACK);
				break;
			case ROOK_BLACK:
				this->_board[q][m] = new Rook(Point(q, m), BLACK_PLAYER_BOARD, ROOK_BLACK);
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
				this->_board[q][m] = new King(Point(q, m), WHITE_PLAYER_BOARD, KING_WHITE);
				break;
			case ROOK_WHITE:
				this->_board[q][m] = new Rook(Point(q, m), WHITE_PLAYER_BOARD, ROOK_WHITE);
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
				this->_board[q][m] = new NullPiece(Point(q,m), NULL_PIECE, NULL_PIECE);
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

Point Board::getKingWhiteLoc() const
{
	//looping on the board and looking for white king.
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (this->_board[i][j]->getPieceColor() == WHITE_PLAYER_BOARD &&
				this->_board[i][j]->getPieceType() == KING_WHITE)
			{
				return this->_board[i][j]->getPieceLoc();
			}
		}
	}
}

Point Board::getKingBlackLoc() const
{
	//looping on the board to search for black king.
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (this->_board[i][j]->getPieceColor() != WHITE_PLAYER_BOARD &&
				this->_board[i][j]->getPieceType() == KING_BLACK)
			{
				return this->_board[i][j]->getPieceLoc();
			}
		}
	}
}

Piece*** Board::getBoard() const
{
	return this->_board;
}

Piece* Board::getPiece(Point src) const
{
	//looking for the piece in the src location.
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

