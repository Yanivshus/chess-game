#pragma once
#include "Piece.h"

class NullPiece : public Piece {
	
	


public:
	NullPiece(const Point& loc, const char color, const char type);
	~NullPiece();
	virtual int checkIfMoveValid(Board*** board) const { return 0; };
	virtual bool checkIfChessKing(Board*** board) const { return false; };
};