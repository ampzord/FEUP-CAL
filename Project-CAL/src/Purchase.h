#ifndef PURCHASE_H
#define PURCHASE_H

#include <string>
#include <vector>

#include "Item.h"

/** \brief class that stores information about a purchases date, if the purchase is finished or not
 * and how many items the purchase is about. */

class Purchase {
private :
    std::string date;
    bool finished;
    std::vector<Item*> items;
public :

    /** \brief Constructor for class Purchase.
     *  \param date Date of purchase.
     *  \param items vector with all of the items purchased. */
    Purchase(std::string date, std::vector<Item*> items);

    /** \brief Returns date of purchase. */
    std::string getDate() const;

    /** \brief Returns vector of items purchased. */
    std::vector<Item*> getItems() const;

    /** \brief Finishes a purchase.
     *  \details changes bool variable finished to true. */
    void finish();
};

#endif
