#include "Truck.h"

#include <algorithm>

using namespace std;

Truck::Truck(double max_weight)
{
	this->max_weight = max_weight;
}

double Truck::getMaxWeight() const
{
	return max_weight;
}

vector<Item*> Truck::getItems() const
{
	return items;
}

void Truck::addItem(Item* item)
{
	items.push_back(item);
}

void Truck::addItems(vector<Item*> items)
{
	this->items = items;
}

void Truck::removeItem(Item* item)
{
	items.erase(remove(items.begin(), items.end(), item), items.end());
}
