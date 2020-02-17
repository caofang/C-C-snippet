// practice of class class

#include <iostream>
#include <string>

#include <stdio.h>
#include "math_class.h"

using namespace std;

int main(int argc, char * argv[])
{
	// circle 
	double radius = 1;
	Circle c1;
	c1.setRadius(radius);
	printf("radius: %g, area: %g, circumference: %g\n", 
		radius, c1.Area(),c1.Circumference());
	printf("get private varible: radius=%g\n", c1.getRadius());


	return 0;
}























