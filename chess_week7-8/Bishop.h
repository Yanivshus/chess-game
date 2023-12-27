#pragma once
#include "Piece.h"

class Bishop : public Piece {
public:
	Bishop(const Point& loc, const char color, const char type);
	~Bishop();
	virtual int checkIfMoveValid(Board* board, const Point& dst) const override;
};