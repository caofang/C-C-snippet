#include <vector>
#include "Circle.h"

class Subject
{
	std::vector<Circle*> circleList;
public:
	void Attach(Circle *c);
	void Detach(Circle *c);
	void Notify(float r);

};