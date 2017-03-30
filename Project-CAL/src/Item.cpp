#include "Item.h"

using namespace std;

Item::Item(string name, double weight)
{
	this->name = name;
	this->weight = weight;
}

string Item::getName() const
{
	return name;
}

double Item::getWeight() const
{
	return weight;
}

bool Item::operator ==(const Item & item) const
{
	return name == item.name;
}
