#pragma once
#include "Piece.h"

//class Piece;
//class Board;

class NullPiece : public Piece {
public:
	NullPiece(const Point& loc, const char color, const char type);
	~NullPiece();

	virtual int checkIfMoveValid(Board* board, const Point& dst) const override { return 0; };
	virtual bool checkIfChessKing(Board* board, const Point& dest) const override { return false; };
};