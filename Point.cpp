//Andrew Niklas
//Homework 5
//Completed

#include "Point.h"

Point::Point()
	:x(0), y(0)
{
	
}

Point::Point(double xValue, double yValue)
	:x(xValue), y(yValue)
{
	
}

Point::Point(const Point& other)
	:x(other.x), y(other.y)
{
	
}

double Point::getX() const{
	return x;
}

double Point::getY() const{
	return y;
}

double Point::xDiff(const Point& right) const{
	return right.x - x;
}

double Point::yDiff(const Point& right) const{
	return right.y - y;
}

double Point::distance(const Point& right) const{
	double dx = xDiff(right);
	double dy = yDiff(right);
	return sqrt((dx * dx) + (dy * dy));
}