#ifndef ITEM_H
#define ITEM_H

#include <string>

//* \brief A class to hold an items name and weight. */

class Item {
private :
	std::string name;
	double weight;

public:

	/** \brief Builds an item.
	 * \param name Name of the item.
	 * \param weight Weight of the item. */
	Item(std::string name, double weight);

	/** \brief Returns the item name. */
	std::string getName() const;

	/** \brief Returns the item weight. */
	double getWeight() const;

	/** \brief Compares two items.
	 *  \details Two items can't have the same node. */
	bool operator== (const Item & item) const;
};

#endif
