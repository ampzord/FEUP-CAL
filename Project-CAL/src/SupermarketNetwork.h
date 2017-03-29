/*
 * SupermarketNetwork.h
 *
 *  Created on: 29/03/2017
 *      Author: furys
 */

#ifndef PROJECT_CAL_SRC_SUPERMARKETNETWORK_H_
#define PROJECT_CAL_SRC_SUPERMARKETNETWORK_H_

#include "Supermarket.h"
#include "graphviewer.h"
#include "Graph.h"

class SupermarketNetwork {
private :
    std::string name;
    GraphViewer* gv;
    Graph<Supermarket> graph;
    int marketId;
public:
	SupermarketNetwork(std::string name);
	void manage();
	void addSupermarket(std::string name);
	bool handleRequest();
	void performOperation(std::string operation);
};

#endif /* PROJECT_CAL_SRC_SUPERMARKETNETWORK_H_ */
