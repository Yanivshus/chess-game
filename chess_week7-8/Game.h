#pragma once
#include <iostream>
#include "Board.h"
#include "NullPiece.h"
#include <string>

#define STARTER_PLAYER 64
#define STARTER_BOARD "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR1"

#define WHITE_PLAYER '0'
#define BLACK_PLAYER '1'

#define OFFSET_Y 'a'
#define OFFSET_X '0'

#define TYPE_NULL '#'

#define VALID_MOVE 0
#define VALID_MOVE_CHESS 1
#define INVALID_MOVE_NO_TOOL_SRC 2
#define INVALID_MOVE_TOOL_AT_DST 3
#define INVALID_MOVE_CHESS_ON_CURRENT 4
#define INVALID_MOVE_OUT_OF_INDEX 5
#define INVALID_MOVE_TOOL_MOVE_NOT_RIGHT 6
#define INVALID_MOVE_SAME_SRC_DST 7

#define SIZE_OF_MOVE 4

#define ROWS 8
#define COLS 8
#define START_ARR  0

class Game {
private:
	char _currPlayer;
	Board* _board;
	Piece* _pieceBefore;
public:
	Game();
	~Game();

	std::string turn(const std::string& playerMove);
	int checkIfTurnPossible(const Point& src, const Point& dst) const;
	std::string getBoardAsString() const;
	void movePiece(const Point& src, const Point& dst);
	void undoMove(const Point& src, const Point& dst);
	int checkForOwnPieceChess(Board* board) const;
	
};