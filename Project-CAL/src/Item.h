#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
private :
	std::string name;
    double weight;

public:
    Item(std::string name, double weight);
    std::string getName() const;
    double getWeight() const;
    bool operator== (const Item & item) const;
};

#endif
