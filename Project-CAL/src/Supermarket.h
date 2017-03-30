#ifndef SUPERMARKET_H
#define SUPERMARKET_H

#include <string>
#include <vector>

#include "Item.h"

class Supermarket {
private :
    std::string name;
    std::vector<Item*> items;
public :
    Supermarket(std::string name);
    Supermarket(std::string name, std::vector<Item*> items);
    std::vector<Item*> getItems() const;
    bool hasItem(Item* item);
    bool operator ==(const Supermarket &b) const;
};

#endif
