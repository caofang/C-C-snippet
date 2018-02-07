// subject
#include <algorithm>
#include <iostream>

#include "Subject.h"

using namespace std;

void Subject::Attach(Circle *c)
{
	circleList.push_back(c);
	// cout << "attach \n";
}

void Subject::Detach(Circle *c)
{
	circleList.erase(std::remove(circleList.begin(), circleList.end(), c),circleList.end());
}

void Subject::Notify(float r)
{
	// cout << "notify \n";
	for(vector<Circle*>::iterator i = circleList.begin(); i != circleList.end(); ++i)
	{
		(*i)->setRadius(r);
		//cout << ' ' << (*i)->getRadius() << "\n";
	}
}

