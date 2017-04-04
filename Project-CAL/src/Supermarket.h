#ifndef SUPERMARKET_H
#define SUPERMARKET_H

#include <string>
#include <vector>

#include "Item.h"

/* A dummy class */
class Supermarket {
private :
    std::string name;
    std::vector<Item*> items;
    int id,x,y;
public :
    Supermarket(std::string name);
    Supermarket(int id, int x, int y);
    Supermarket(std::string name, std::vector<Item*> items);
    std::vector<Item*> getItems() const;
    bool hasItem(Item* item);
    bool operator ==(const Supermarket &b) const;
    int getId() const;
    int getX() const;
    int getY() const;
};

#endif
