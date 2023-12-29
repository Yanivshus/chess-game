#pragma once
#include "Piece.h"
#define OFFSET 1

class King : public Piece {
public:

	King(const Point& loc, const char color, const char type);
	~King();
	/// <summary>
	/// checking if king movement is right.
	/// </summary>
	/// <param name="board:">game board.</param>
	/// <param name="dst:"> dst move.</param>
	/// <returns>code.</returns>
	virtual int checkIfMoveValid(Board* board, const Point& dst) const override;
	
};