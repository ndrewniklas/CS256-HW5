//Andrew Niklas
//Homework 5
//Completed

#include "Particle.h"
#include <iostream>


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

void Particle::updateVelocity(Point a, double dt){
	velocity.x = velocity.x + a.x * dt;
	velocity.y = velocity.y + a.y * dt;
}

void Particle::updatePos(Point a, double dt){
	std::cout << "x0 = " << position.x << std::endl;
	std::cout << "y0 = " << position.y << std::endl;
	double n = 0.5;
	position.x += velocity.x * dt + (n * a.x * (dt * dt));
	position.y += velocity.y * dt + (n * a.y * (dt * dt));
	
	std::cout << "x = " << position.x << std::endl;
	std::cout << "y = " << position.y << std::endl;
}