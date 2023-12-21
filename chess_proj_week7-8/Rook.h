#pragma once
#include "Piece.h"

class Rook : public Piece {
	Rook(const Point& loc, const char color, const char type);
	~Rook();

	virtual bool checkIfChessKing() const override;
	virtual int checkIfMoveValid() const override;
};