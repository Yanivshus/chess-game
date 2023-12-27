#pragma once
#include "Piece.h"

class Queen : public Piece {
public:
	Queen(const Point& loc, const char color, const char type);
	~Queen();
	virtual int checkIfMoveValid(Board* board, const Point& dst) const override;
};