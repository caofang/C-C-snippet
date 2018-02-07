// vector 
#include <iostream>
#include <vector>
#include <algorithm>


// #include "Circle.h"
// #include "Subject.h"
#include "Radius.h"

using namespace std;

int main ()
{

	Radius radius;
	Circle c1, c2, c3;


	radius.Attach(&c1);
	radius.Attach(&c2);
	radius.Attach(&c3);

	radius.ChangeRadius(1);
	cout << "c2.getRadius() " << c2.getRadius() << "\n";
	cout << "c2.getArea() " << c2.getArea() << "\n";
	cout << "c2.getCircumference() " << c2.getCircumference() << "\n";

	radius.Detach(&c2);

	radius.ChangeRadius(10);
	cout << "c2.getRadius() " << c2.getRadius() << "\n";
	cout << "c2.getArea() " << c2.getArea() << "\n";
	cout << "c2.getCircumference() " << c2.getCircumference() << "\n";






	return 0;
}