#pragma once
#include "Piece.h"

class Knight : public Piece {
public:
	Knight(const Point& loc, const char color, const char type);
	~Knight();
	virtual int checkIfMoveValid(Board* board, const Point& dst) const override;
};