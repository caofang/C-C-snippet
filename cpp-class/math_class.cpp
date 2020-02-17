// practice of class class

#include "math_class.h"

Circle::Circle(void)
{

}

void Circle::setRadius(double r)
{
	radius = r;
}

double Circle::getRadius()
{
	return radius;
}

double Circle::Area()
{
	return 3.14 * radius * radius;
}

double Circle::Circumference()
{
	return 2 * 3.14 * radius;
}
