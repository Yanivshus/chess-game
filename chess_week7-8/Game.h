#pragma once
#include <iostream>
#include "Board.h"
#include "NullPiece.h"
#include <string>

#define STARTER_PLAYER 64
//originial = "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR1"
#define STARTER_BOARD "r###k##r################################################R##K###R0"

#define WHITE_PLAYER '0'
#define BLACK_PLAYER '1'

#define OFFSET_Y 'a'
#define OFFSET_X '0'
#define X_NULLER_OFFSET 1

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

	/// <summary>
	/// we will menaged most of the game in turn.
	/// player switces, and the whole game checks.
	///	meant also for moving players.
	/// </summary>
	/// <param name="playerMove:">the player move we will get from the frontend.</param>
	/// <returns>all posiible code: 1-8</returns>
	std::string turn(const std::string& playerMove);

	/// <summary>
	/// checks if there is a movement to the same place.
	/// if there is a player from the same color in the dest.
	/// if the dst and src are the same point.
	/// if the dst and src are in the board limits.
	/// </summary>
	/// <param name="src:">move from cord</param>
	/// <param name="dst:">move to cord</param>
	/// <returns></returns>
	int checkIfTurnPossible(const Point& src, const Point& dst) const;
	
	/// <summary>
	/// return the board as a string.
	/// </summary>
	/// <returns>std::string board values.</returns>
	std::string getBoardAsString() const;

	/// <summary>
	/// moves a piece from src to dst.
	/// </summary>
	/// <param name="src:">point to move from.</param>
	/// <param name="dst:">point to move to.</param>
	void movePiece(const Point& src, const Point& dst);
	
	/// <summary>
	/// undos a move made on a player.
	/// </summary>
	/// <param name="src:">point to move from.</param>
	/// <param name="dst">point to move to.</param>
	void undoMove(const Point& src, const Point& dst);

	/// <summary>
	/// checks if the is a chess on the king from the same color after a move is made.
	/// </summary>
	/// <param name="board:">board of the game.</param>
	/// <returns>4 if chess was made.</returns>
	int checkForOwnPieceChess(Board* board) const;

	/// <summary>
	/// checks if there is chesss on op king by a curr player move.
	/// </summary>
	/// <param name="board:">board of the game.</param>
	/// <param name="toCheck:">piece to check on.</param>
	/// <returns>1 if a chess were made 0 if not.</returns>
	int checkForChessOnOp(Board* board, Piece* toCheck);
	
};