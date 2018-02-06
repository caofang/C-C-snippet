// practice of class class

#include <iostream>
#include <string>

#include <stdio.h>

using namespace std;

class Fang_1
{
	private:

	public:
		void coolSaying()
		{
			printf("hello\n");
		}
	
};

class Fang_2
{
	private:
		string name;
	public:
		void setName(string x)
		{	
			name = x;
		}
		string getName()
		{
			return name;
		}	
};

class Circle
{

	private:
		double radius;

	public:
		double getRadius()
		{
			return radius;
		}
		double area(double r)
		{
			radius = r;
			return 3.14 * radius * radius;
		}

		double circumference(double r)
		{
			radius = r;
			return 2 * 3.14 * radius;
		}
};

int main(int argc, char * argv[])
{
	// class 1 
	Fang_1 f_object;
	f_object.coolSaying();

	// class 2
	Fang_2 c2;
	c2.setName("hello world\n");
	cout << c2.getName();

	// circle 
	double radius = 1;
	Circle c1;
	printf("radius: %g, area: %g, circumference: %g\n", 
		radius, c1.area(radius),c1.circumference(radius));
	printf("get private varible: radius=%g\n", c1.getRadius());


	return 0;
}























