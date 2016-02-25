//Andrew Niklas
//Homework 5
//Completed

#include "Particle.h"


Particle::Particle(Point pos, double m)
	:position(pos),velocity(0,0), 
	mass(m), radius(setRadius())
{
	
}

double Particle::setRadius(){
	return ((mass/MAX_MASS)*20 + 3);
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