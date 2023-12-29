#pragma once
#include "Piece.h"

class Queen : public Piece {
public:
	Queen(const Point& loc, const char color, const char type);
	~Queen();
	/// <summary>
	/// checks if queen moved right.
	/// </summary>
	/// <param name="board:">game board.</param>
	/// <param name="dst:">dst move.</param>
	/// <returns>code.</returns>
	virtual int checkIfMoveValid(Board* board, const Point& dst) const override;
};