//Andrew Niklas
//Homework 5
//Completed

#ifndef PARTICLE_H
#define	PARTICLE_H

#include "Point.h"
#include "Constants.h"
class Particle
{
private:
	Point position;
	Point velocity;
	double mass;
	double radius;
	double setRadius();
	
public:
	Particle(Point pos, double mass);
	Point getPos() const;
	Point getVelocity() const;
	double getMass() const;
	double getRadius() const;
	
	void updateVelocity(Point accel, double time);
	void updateVelocity(double x, double y);
	void updatePos(double dt);
	void negateVelocity(char component);
	double velocityMagnitude() const;
	double velocityAngle() const;
	
	void destroy();
};

#endif