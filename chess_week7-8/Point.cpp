#include "Point.h"

Point::Point()
{
	this->_x = 0;
	this->_y = 0;
}

Point::Point(const int x, const int y)
{
	this->_x = x;
	this->_y = y;
}

Point::~Point()
{
	this->_x = 0;
	this->_y = 0;
}

Point Point::operator+(const Point& other) const
{
	//conatracting new point with x and y values.
	Point pointToReturn(this->_x + other.getX(), this->_y + other.getY());
	return pointToReturn;
}

Point& Point::operator+=(const Point& other)
{
	this->_x += other.getX();
	this->_y += other.getY();
	return *this;
}

int Point::getX() const
{
	return this->_x;
}

int Point::getY() const
{
	return this->_y;
}

void Point::setX(const int x)
{
	this->_x = x;
}

void Point::setY(const int y)
{
	this->_y = y;
}
