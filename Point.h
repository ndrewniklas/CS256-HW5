//Andrew Niklas
//Homework 5
//Completed

#ifndef POINT_H
#define POINT_H

class Point
{
private:
	double x;
	double y;
public:
	Point(double x, double y);
	Point(const Point& other);
	double getX() const;
	double getY() const;
	
};

#endif