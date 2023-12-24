#pragma once
#include "Piece.h"
#define OFFSET 1

class King : public Piece {
public:

	King(const Point& loc, const char color, const char type);
	~King();

	virtual int checkIfMoveValid(Board* board, const Point& dst) const override;
	
};