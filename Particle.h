//Andrew Niklas
//Homework 5
//Completed

#ifndef PARTICLE_H
#define	PARTICLE_H

#include "Point.h"
class Particle
{
private:
	Point position;
	Point velocity;
	double mass;
	double radius;
	
public:
	Particle(Point pos, double mass);
	Point getPos() const;
	Point getVelocity() const;
	double getMass() const;
	double getRadius() const;
	
};

#endif