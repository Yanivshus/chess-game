#pragma once
#include "Piece.h"

#define TRUE 1
#define FALSE 0

class Pawn : public Piece {
private:
	mutable int _isFirst;
public:
	Pawn(const Point& loc, const char color, const char type);
	~Pawn();
	/// <summary>
	/// checks if a move is valid for pawn.
	/// valid is move is one square diagmall if can eat.
	/// two square forward if first move.
	/// one squaere if not.
	/// </summary>
	/// <param name="board:">game board.</param>
	/// <param name="dst:">dst to move.</param>
	/// <returns>code</returns>
	virtual int checkIfMoveValid(Board* board, const Point& dst) const override;
};