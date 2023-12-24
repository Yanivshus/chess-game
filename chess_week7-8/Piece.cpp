#include "Piece.h"



Piece::Piece(const Point& loc, const char color, const char type)
{
	this->_loc = loc;
	this->_color = color;
	this->_type = type;
}

Piece::~Piece()
{
}

char Piece::getPieceType()
{
	return this->_type;
}

char Piece::getPieceColor()
{
	return this->_color;
}

void Piece::setLoc(const Point& other)
{
	this->_loc.setX(other.getX());
	this->_loc.setY(other.getY());
}

Point Piece::getPieceLoc()
{
	return this->_loc;
}
