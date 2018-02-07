#include "Circle.h"
#include <iostream>

#define PI 3.14

Circle::Circle()
{

}

// will automatically compute area and circumference
void Circle::setRadius(float r)
{
	this->radius = r;
	setArea();
	setCircumference();
}

float Circle::getRadius()
{
	return this->radius;
}

float Circle::getArea()
{
	return this->area;
}

float Circle::getCircumference()
{
	return this->circumference;
}

void Circle::setArea()
{
	this->area = PI * (this->radius) * (this->radius);
}

void Circle::setCircumference()
{
	this->circumference = 2 * PI;
}

