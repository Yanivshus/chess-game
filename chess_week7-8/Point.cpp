#include "Point.h"

Point::Point()
{
	this->_x = 0;
	this->_y = 0;
}

Point::Point(const double x, const double y)
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

double Point::getX() const
{
	return this->_x;
}

double Point::getY() const
{
	return this->_y;
}

void Point::setX(const double x)
{
	this->_x = x;
}

void Point::setY(const double y)
{
	this->_y = y;
}
