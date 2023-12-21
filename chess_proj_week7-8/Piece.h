#pragma once
#include "Point.h"
#include <iostream>

#define VALID_MOVE 0
#define VALID_MOVE_CHESS 1
#define INVALID_MOVE_NO_TOOL_SRC 2
#define INVALID_MOVE_TOOL_AT_DST 3
#define INVALID_MOVE_CHESS_ON_CURRENT 4
#define INVALID_MOVE_OUT_OF_INDEX 5
#define INVALID_MOVE_TOOL_MOVE_NOT_RIGHT 6
#define INVALID_MOVE_SAME_SRC_DST 7

#define ROW_SPOT 0

class Piece {
protected:
	Point _loc;
	char _color;
	char _type;
public:
	Piece(const Point& loc, const char color, const char type);
	virtual ~Piece();
	virtual int checkIfMoveValid() const = 0;
	//virtual int move(const std::string& srcToDst) = 0;
	char getPieceType();
	char getPieceColor();
	Point getPieceLoc();
	virtual bool checkIfChessKing() const = 0;
};
