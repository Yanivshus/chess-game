#pragma once
#include "Piece.h"
#include "Point.h"
//#include "NullPiece.h"
#include <iostream>

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

#define COLOR_OF_NULL_PIECE '\0'

class Piece;
//class NullPiece;

class Board {
private:
	Piece*** _board;
	Point _kingWhiteLoc;
	Point _kingBlackLoc;
public:
	Board(const std::string& board);
	~Board();

	Piece*** getBoard() const;
	Piece* getPiece(Point src) const;

};