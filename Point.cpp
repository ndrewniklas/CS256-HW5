//Andrew Niklas
//Homework 5
//Completed

#include "Point.h"


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