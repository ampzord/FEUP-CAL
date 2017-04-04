#include "Truck.h"

#include <algorithm>

using namespace std;

/**
 * \brief Construtor da classe Truck com argumentos.
 * \param max_weight Peso maximo suportado pelo camiao.
 */
Truck::Truck(double max_weight)
{
	this->max_weight = max_weight;
}

/**
 * \brief Retorna o peso maximo suportado pelo camiao.
 */
double Truck::getMaxWeight() const
{
	return max_weight;
}

/**
 * \brief Retorna o vector de Items do camiao.
 */
vector<Item*> Truck::getItems() const
{
	return items;
}

/**
 * \brief Adiciona um Item ao camiao.
 * \param Item* item Item a ser adicionado ao vector items[].
 */
void Truck::addItem(Item* item)
{
	items.push_back(item);
}

/**
 * \brief Torna os Items do camiao os Items passados como argumento.
 * \param vector<Item *>items Items a ser guardados no vetor items[] do camiao.
 */
void Truck::addItems(vector<Item*> items)
{
	this->items = items;
}

/**
 * \brief Remove o Item passado como argumento do camiao.
 * \param Item* item Item a ser removido do vector items[].
 */
void Truck::removeItem(Item* item)
{
	items.erase(remove(items.begin(), items.end(), item), items.end());
}

/**
 * \brief Retorna o peso restante suportado pelo camiao.
 */
double Truck::getFreeWeight() const {
	double truckWeight = 0;
	for (unsigned int i = 0;i<=items.size();i++)
		truckWeight += items[i]->getWeight();
	return max_weight - truckWeight;
}
