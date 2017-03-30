#ifndef PURCHASE_H
#define PURCHASE_H

#include <string>
#include <vector>

#include "Item.h"

class Purchase {
private :
    std::string date;
    bool finished;
    std::vector<Item*> items;
public :
    Purchase(std::string date, std::vector<Item*> items);
    std::string getDate() const;
    std::vector<Item*> getItems() const;
    void finish();
};

#endif
