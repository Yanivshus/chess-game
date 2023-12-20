#pragma once
#include "Piece.h"
#include <iostream>


class NullPiece : public Piece {
	public:
		NullPiece(const Point& loc, const char color, const char type);
		~NullPiece();

		//in the null piece those functions aren't used.
		virtual int checkIfMoveValid() const {};
		virtual bool checkIfChessKing() const {};
};