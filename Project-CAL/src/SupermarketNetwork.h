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
#include "Node.h"
#include "FakeEdge.h"

#define PI 3.14159265358979323846

/* A dummy class */
class SupermarketNetwork {
private :
    std::string name;
    GraphViewer* gv;
    Graph<Supermarket> graph;
    Graph<Node> fake_graph;
    int marketId;
    std::vector<Supermarket> markets;
    std::vector<Node> nodes;
    std::vector<FakeEdge> edges;
public:
	SupermarketNetwork(std::string name);
	void manage();
	void addSupermarket(std::string name);
	bool handleRequest();
	void performOperation(std::string operation);
	void loadMarkets();
	void loadNodesRandom();
	void loadNodeInformation();
	void loadStreetInformation();
	void loadEdgeInformation();
	void loadFakeEdges();
	void paintLoaded();
	int getEdgePosById(unsigned long long id);
	bool isEdgePosById(unsigned long long id);
	void printResults(map<int, vector<int> > res);
	double distanceBetween2Nodes(double lat1, double lat2, double long1, double long2);
};

#endif /* PROJECT_CAL_SRC_SUPERMARKETNETWORK_H_ */
