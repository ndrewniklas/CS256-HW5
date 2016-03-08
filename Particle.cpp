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

void Particle::updateVelocity(double x, double y){
	velocity.x = x;
	velocity.y = y;
	//if(velocityMagnitude() > 5e+4){
	//	velocity.x = x / 1e+4;
	//	velocity.y = y / 1e+4;
	//}
}

void Particle::updatePos(double dt){
	position.x += velocity.x * dt;
	position.y += velocity.y * dt;
}

void Particle::negateVelocity(char component){
	if(component == 'x'){
		velocity.x = -velocity.x;
	}else if(component == 'y'){
		velocity.y = -velocity.y;
	}
}

double Particle::velocityMagnitude() const{
	return sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));
}

double Particle::velocityAngle() const{
	return atan2(velocity.y, velocity.x);
}

















