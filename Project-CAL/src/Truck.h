#ifndef TRUCK_H
#define TRUCK_H

#include <vector>

#include "Item.h"

/** \brief class that holds each truck max_weight and all their items. */

class Truck {
private :
	double max_weight;
	std::vector<Item*> items;

public :

	/**
	 * \brief Constructor of class Truck.
	 * \param max_weight Max weight supported by the truck. */
	Truck(double max_weight);

	/**
	 * \brief Returns the maximum weight supported by the truck. */
	double getMaxWeight() const;

	/**
	 * \brief Returns a vector of items that the truck posseses. */
	std::vector<Item*> getItems() const;

	/**
	 * \brief Adds one item to the truck.
	 * \param item is the item to be added to the vector. */
	void addItem(Item* item);

	/**
	 * \brief Replaces the truck items with the ones from it's argument.
	 * \param items Items is the vector of Items to replace the current truck items. */
	void addItems(std::vector<Item*> items);

	/**
	 * \brief Removes one item from it's truck.
	 * \param item Item is the item to be removed from the vector of items. */
	void removeItem(Item* item);

	/**
	 * \brief Returns the free weight of the truck. */
	double getFreeWeight() const;
};

#endif
