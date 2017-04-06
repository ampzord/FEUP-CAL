#ifndef PROJECT_CAL_SRC_SUPERMARKETNETWORK_H_
#define PROJECT_CAL_SRC_SUPERMARKETNETWORK_H_

#include "graphviewer.h"
#include "Graph.h"
#include "Node.h"
#include "FakeEdge.h"
#include <stdlib.h>
#include <time.h>
#include <sys/timeb.h>

#define PI 3.14159265358979323846

class SupermarketNetwork {
private :
    std::string name;
    GraphViewer* gv;
    Graph<Node> fake_graph;
    int marketId;
    std::vector<Node> nodes;
    std::vector<FakeEdge> edges;
public:

    /**
     * \brief Constructor of class SupermarketNetwork
     * \param name name of the Supermarket */
	SupermarketNetwork(std::string name);
	/**
	 * \brief Loads nodes from text file giving them a random type. */
	void loadNodesRandom();

	/**
	 * \brief Loads street information from text file */
	void loadStreetInformation();
	/**
	 * \brief Loads edge information from text file. */
	void loadEdgeInformation();

	/**
	 * \brief Inserts on graph the nodes and edges along as
	 * giving them their current color on graphviewer. */
	void paintLoaded();

	/**
	 * \brief Returns the position of an edge on a vector by it's ID. */
	int getEdgePosById(unsigned long long id);

	/**
	 * \brief Checks if there exists already any edge with the ID given. */
	bool isEdgePosById(unsigned long long id);

	/**
	 * \brief Writes on file the results of application of the algorithms.
	 * \details argument is map<int, vector<int> >*/
	void printResults(map<int, vector<int> > res);

	/**
	 * \brief Writes on file the results of application of the algorithms.
	 * \details argument is vector<pair<int, vector<int> > > */
	void printResults(vector<pair<int, vector<int> > > res);

	/**
	 * \brief Calculates the distance between 2 nodes. */
	double distanceBetween2Nodes(double lat1, double lat2, double long1, double long2);

	/** \brief Main Menu with interface. */
	void mainMenu();

	/**\brief Gives option to user to choose between several algorithms. */
	void chooseAlgorithmFromOpenStreetMapsGraph();

	/** \brief Loads all information from text files simultaneously. */
	void loadInformationOpenStreetMapsGraph();

	/** \brief Calculates the time each algorithm takes and saves it to a text file. */
	void runTime();
};

#endif /* PROJECT_CAL_SRC_SUPERMARKETNETWORK_H_ */
