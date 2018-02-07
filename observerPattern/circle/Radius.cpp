#include "Radius.h"
#include <iostream>

void Radius::ChangeRadius(float radius)
{
	// std::cout << "Notify: " << radius << "\n"; 
	Notify(radius);
}