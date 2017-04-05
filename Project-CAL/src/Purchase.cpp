#include "Purchase.h"

using namespace std;

Purchase::Purchase(string date, vector<Item*> items)
{
	this->date = date;
	this->items = items;
	this->finished = false;
}

string Purchase::getDate() const
{
	return date;
}

vector<Item*> Purchase::getItems() const
{
	return items;
}

void Purchase::finish()
{
	finished = true;
}
