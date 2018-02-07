#include "Shop.h"


Shop::Shop(std::string name)
{
	this->name = name;

}

void Shop::Update(float price)
{
	this->price = price;
	std::cout << "Price at " << name << " is: " << price << "\n";
}

float Shop::getPrice()
{
	return this->price;
}