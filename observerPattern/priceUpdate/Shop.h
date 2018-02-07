#pragma once

//#include "Observer.h"
#include "string"
#include "iostream"

class Shop
{
	std::string name;
	float price;
public:
	Shop(std::string n);
	void Update(float price);
	float getPrice();
};

