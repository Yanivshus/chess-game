#pragma once

#define POWER 2
class Point
{
public:


	Point(); // initialize values to 0

	/// <summary>
	/// sets values of x and y;
	/// </summary>
	/// <param name="x:">the x value.</param>
	/// <param name="y:">the y value</param>
	Point(const double x, const double y);

	// Destructor
	~Point();

	/// <summary>
	/// operator overload to add two points together and return the result.
	/// </summary>
	/// <param name="other:">the other point to add.</param>
	/// <returns>the new point after addition.</returns>
	Point operator+(const Point& other) const;

	/// <summary>
	/// operator overload to add a point the current point.
	/// </summary>
	/// <param name="other:">point to add.</param>
	/// <returns>reference to the point after addition.</returns>
	Point& operator+=(const Point& other);

	/// <summary>
	/// return the x coordinent.
	/// </summary>
	/// <returns>the x oordinent.</returns>
	double getX() const;

	/// <summary>
	/// return the y coordinent.
	/// </summary>
	/// <returns>the y oordinent.</returns>
	double getY() const;
	
	void setX(const double x);
	void setY(const double y);
	

private:
	double _x;
	double _y;

};