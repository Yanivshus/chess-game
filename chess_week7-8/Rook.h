#pragma once
#include "Piece.h"
class Rook : public Piece {
public:
	Rook(const Point& loc, const char color, const char type);
	~Rook();
	virtual int checkIfMoveValid(Board*** board) const override;
	virtual bool checkIfChessKing(Board*** board) const override;
};