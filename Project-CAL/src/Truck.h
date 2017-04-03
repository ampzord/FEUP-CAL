#ifndef TRUCK_H
#define TRUCK_H

#include <vector>

#include "Item.h"

class Truck {
private :
    double max_weight;
    std::vector<Item*> items;

public :
    Truck(double max_weight);
    double getMaxWeight() const;
    std::vector<Item*> getItems() const;
    void addItem(Item* item);
    void addItems(std::vector<Item*> items);
    void removeItem(Item* item);
    double getFreeWeight() const;
};

#endif
