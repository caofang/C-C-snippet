// vector 
#include <iostream>
#include <vector>
#include <algorithm>


#include "Circle.h"

using namespace std;
int main ()
{

	Circle c1, c2, c3;
	(c1).setRadius(1);
	(c2).setRadius(2);
	(c3).setRadius(3);

	// attach
	std::vector<Circle*> myvector;
	myvector.push_back(&c1);
	myvector.push_back(&c2);
	myvector.push_back(&c3);

	cout << "myvector contains:";
	for (vector<Circle*>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
	cout << ' ' << (*it)->getRadius();
	cout << '\n';

	// remove
	// myvector.erase(myvector.begin() +1);
	myvector.erase(std::remove(myvector.begin(), myvector.end(), &c1), myvector.end());

	//myvector.erase( std::remove( myvector.begin(), myvector.end(), c1 ), myvector.end() ); 

	cout << "myvector contains:";
	for (vector<Circle*>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
	cout << ' ' << (*it)->getRadius();
	cout << '\n';


	return 0;
}