#pragma once
#include "Board.h"
#include "Point.h"

#define VALID_MOVE 0
#define VALID_MOVE_CHESS 1
#define INVALID_MOVE_NO_TOOL_SRC 2
#define INVALID_MOVE_TOOL_AT_DST 3
#define INVALID_MOVE_CHESS_ON_CURRENT 4
#define INVALID_MOVE_OUT_OF_INDEX 5
#define INVALID_MOVE_TOOL_MOVE_NOT_RIGHT 6
#define INVALID_MOVE_SAME_SRC_DST 7

#define ROW_SPOT 0

class Board;

class Piece {
protected:
	Point _loc;
	char _color;
	char _type;
public:
	/// <summary>
	/// constractor for abstract piece.
	/// </summary>
	/// <param name="loc:">loaction of the piece.</param>
	/// <param name="color:">color of the piece.</param>
	/// <param name="type:">type of the piece.</param>
	Piece(const Point& loc, const char color, const char type);
	virtual ~Piece();

	/// <summary>
	/// check if the piece movment is valid.
	/// </summary>
	/// <param name="board:">game board.</param>
	/// <param name="dst:">where the piece moving to.</param>
	/// <returns></returns>
	virtual int checkIfMoveValid(Board* board, const Point& dst) const = 0;
	
	//getters and setters for fields.
	char getPieceType();
	char getPieceColor();
	void setLoc(const Point& other);
	Point getPieceLoc();
	
};