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

void Particle::updateVelocity(Point a, double dt){
	velocity.x = velocity.x + a.x * dt;
	velocity.y = velocity.y + a.y * dt;
}

void Particle::updatePos(Point a, double dt){
	position.x += velocity.x * dt + (0.5 * a.x * (dt * dt));
	position.y += velocity.y * dt + (0.5 * a.y * (dt * dt));
}