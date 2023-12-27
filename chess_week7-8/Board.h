#pragma once
#include "Piece.h"
#include "Point.h"
#include <iostream>

#define ROWS 8
#define COLS 8

#define KING_BLACK 'K'
#define ROOK_BLACK 'R'
#define PAWN_BLACK 'P'
#define KNIGHT_BLACK 'N'
#define BISHOP_BLACK 'B'
#define QUEEN_BLACK 'Q'

#define KING_WHITE 'k'
#define ROOK_WHITE 'r'
#define PAWN_WHITE 'p'
#define KNIGHT_WHITE 'n'
#define BISHOP_WHITE 'b'
#define QUEEN_WHITE 'q'

#define NULL_PIECE '#'
#define WHITE_PLAYER_BOARD '0'
#define BLACK_PLAYER_BOARD '1'

#define COLOR_OF_NULL_PIECE '\0'

class Piece;
//class NullPiece;

class Board {
private:
	Piece*** _board;
public:
	/// <summary>
	/// constractor for the board which taked a board string and turns it to a 2d array of allocated pieces.
	/// </summary>
	/// <param name="board:">string which represent the board.</param>
	Board(const std::string& board);

	/// <summary>
	/// deletes all allocated memory for the board.
	/// </summary>
	~Board();

	/// <summary>
	/// getting the white king location.
	/// </summary>
	/// <returns>Point of the white king</returns>
	Point getKingWhiteLoc() const;

	/// <summary>
	/// getting the black king location.
	/// </summary>
	/// <returns>Point of the black king.</returns>
	Point getKingBlackLoc() const;


	/// <returns>pointer to the board.</returns>
	Piece*** getBoard() const;
	
	/// <summary>
	/// getting a piece pointer by location on the board.
	/// </summary>
	/// <param name="src:">location of the piece.</param>
	/// <returns>Piece* src piece.</returns>
	Piece* getPiece(Point src) const;

};