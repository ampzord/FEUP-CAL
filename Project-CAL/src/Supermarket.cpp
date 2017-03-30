#include "Supermarket.h"
#include <algorithm>

using namespace std;

Supermarket::Supermarket(std::string name) {
    this->name = name;
}

Supermarket::Supermarket(std::string name, std::vector<Item*> items) {
    this->name = name;
    this->items = items;
}

bool Supermarket::operator ==(const Supermarket & b) const
{
	return name == b.name;
}

std::vector<Item*> Supermarket::getItems() const
{
	return items;
}

bool Supermarket::hasItem(Item* item)
{
	return find(items.begin(), items.end(), item) != items.end();
}
