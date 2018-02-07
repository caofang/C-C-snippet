#pragma once
#include "Subject.h"

class DummyProduct : public Subject
{
public:
	void ChangePrice(float price);
};