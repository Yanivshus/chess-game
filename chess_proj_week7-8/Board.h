#pragma once
#include <iostream>
#include "Point.h"
#include "Piece.h"
#define ROWS 8
#define COLS 8

#define KING_BLACK 'K'
#define ROOK_BLACK 'R'
#define PAWN_BLACK 'P'
#define KNIGHT_BLACK 'N'
#define BISHOP_BLACK 'B'
#define QUEEN_BLACK 'Q'

#define KING_WHITE 'k'
#define ROOK_WHITE 'r'
#define PAWN_WHITE 'p'
#define KNIGHT_WHITE 'n'
#define BISHOP_WHITE 'b'
#define QUEEN_WHITE 'q'

#define NULL_PIECE '#'

class Board {
	private:
		Piece* _board[ROWS][COLS];
		Point _kingWhiteLoc;
		Point _kingBlackLoc;
		void setBoard(const std::string& board);
	public:
		Board(const std::string& board);
		~Board();

		Piece* getPiece(Point src) const;
		Point destructLocation(const std::string& loc) const;
};
