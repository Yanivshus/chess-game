#pragma once
#include "Point.h"
#include <iostream>
#define ROW_SPOT 0

class Piece {
protected:
	Point _loc;
	char _color;
	char _type;
public:
	Piece(const Point& loc, const char color, const char type);
	~Piece();
	virtual int checkIfMoveValid() const = 0;
	virtual int move(const std::string& srcToDst) = 0;
	char getPieceType();
	char getPieceColor();
	Point getPieceLoc();
	virtual bool checkIfChessKing() const = 0;
};
