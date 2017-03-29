#include "Supermarket.h"

Supermarket::Supermarket(std::string name) {
    this->name = name;
}

bool Supermarket::operator ==(const Supermarket & b) const
{
	return name == b.name;
}
