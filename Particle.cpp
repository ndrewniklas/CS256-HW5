//Andrew Niklas
//Homework 5
//Completed

#include "Particle.h"
#include "Point.h"


Particle::Particle(Point pos, double m)
	:position(pos),velocity(0,0), mass(m)
{
	
}

Point Particle::getPos() const{
	return position;
}

Point Particle::getVelocity() const{
	return velocity;
}

double Particle::getMass() const{
	return mass;
}

double Particle::getRadius() const{
	return radius;
}