//Andrew Niklas
//Homework 5
//Completed

#ifndef POINT_H
#define POINT_H

#include <cmath>
class Point
{
	friend class Particle;
	
private:
	double x;
	double y;
public:
	Point();
	Point(double x, double y);
	Point(const Point& other);
	double getX() const;
	double getY() const;
	
	double xDiff(const Point& right) const;
	double yDiff(const Point& right) const;
	double distance(const Point& right) const;
	
};

#endif