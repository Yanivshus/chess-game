#pragma once
#include "Piece.h"

class Knight : public Piece {
public:
	Knight(const Point& loc, const char color, const char type);
	~Knight();
	/// <summary>
	/// checking if knight move is right.
	/// </summary>
	/// <param name="board:">game board.</param>
	/// <param name="dst:">dst move.</param>
	/// <returns>code</returns>
	virtual int checkIfMoveValid(Board* board, const Point& dst) const override;
};