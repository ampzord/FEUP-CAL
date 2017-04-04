/*
 * SupermarketNetwork.cpp
 *
 *  Created on: 29/03/2017
 *      Author: furys
 */

#include "SupermarketNetwork.h"
#include "Supermarket.h"
#include "Node.h"
#include <fstream>
#include <sstream>

using namespace std;

SupermarketNetwork::SupermarketNetwork(std::string name) {
	// TODO Auto-generated constructor stub

	this->name = name;
	this->gv = new GraphViewer(1000, 600, true);

	gv->createWindow(1000, 600);

	gv->defineVertexColor("blue");

	gv->defineEdgeColor("black");

	loadNodesRandom();
	loadFakeEdges();
	//loadMarkets();

	/*for (size_t i = 0; i < markets.size(); i++) {
	 gv->addNode(markets[i].getId());
	 }*/

	/*
	 for (size_t i = 0; i < nodes.size(); i++) {
	 gv->addNode(nodes[i].getNodeId());
	 if (nodes[i].getType() == 0)
	 gv->setVertexColor(nodes[i].getNodeId(), "yellow");
	 if (nodes[i].getType() == 1)
	 gv->setVertexColor(nodes[i].getNodeId(), "green");
	 }

	 for (size_t i = 0; i < edges.size(); i++) {
	 if(edges[i].getEdgeId() != edges[i-1].getEdgeId() && edges[i].getV1Id() != edges[i].getV2Id())
	 gv->addEdge(edges[i].getEdgeId(), edges[i].getV1Id(),
	 edges[i].getV2Id(), 0);
	 }
	 */

	marketId = 0;
}

void SupermarketNetwork::manage() {

	Supermarket x(name);
		Supermarket y("asd");
		Supermarket z("asdadas");
		Supermarket w("asdasdasdasdsa");
		Supermarket u("sadsadasdsadasdas");
		Supermarket i("sadsadasdsadasdas23");
		Supermarket a("sadsadasdsadasdasasds23");

		graph.addVertex(x, "Market", 0);

		graph.addVertex(y, "User", 1);
		graph.addVertex(z, "User", 2);

		graph.addVertex(w, "Nothing", 3);
		graph.addVertex(u, "Nothing", 4);
		graph.addVertex(i, "Market", 5);
		graph.addVertex(a, "User", 6);

		graph.addEdge(x, w, 100);
		graph.addEdge(w, x, 100);

		graph.addEdge(x, u, 200);
		graph.addEdge(u, x, 200);

		graph.addEdge(w, y, 100);
		graph.addEdge(y, w, 100);

		graph.addEdge(u, z, 200);
		graph.addEdge(z, u, 200);

		graph.addEdge(z, y, 400);
		graph.addEdge(y, z, 400);

		graph.addEdge(i, y, 200);
		graph.addEdge(y, i, 200);

		graph.addEdge(a, x, 300);
		graph.addEdge(x, a, 300);

		graph.addEdge(w, u, 200);
		graph.addEdge(u, w, 200);

		graph.addEdge(y, u, 100);
		graph.addEdge(u, y, 100);

		graph.addEdge(w, z, 250);
		graph.addEdge(z, w, 250);

		gv->addNode(marketId);

		gv->setVertexLabel(marketId, "0");

		marketId++;

		gv->addNode(marketId);

		gv->setVertexLabel(marketId, "1");

		marketId++;

		gv->addNode(marketId);

		gv->setVertexLabel(marketId, "2");

		marketId++;

		gv->addNode(marketId);

		gv->setVertexLabel(marketId, "3");

		marketId++;

		gv->addNode(marketId);

		gv->setVertexLabel(marketId, "4");

		marketId++;

		gv->addNode(marketId);

		gv->setVertexLabel(marketId, "5");

		marketId++;

		gv->addNode(marketId);

		gv->setVertexLabel(marketId, "6");

		marketId++;

		gv->setVertexColor(0, "green");
		gv->setVertexColor(5, "green");

		gv->setVertexColor(1, "yellow");
		gv->setVertexColor(2, "yellow");
		gv->setVertexColor(6, "yellow");

		gv->addEdge(0, 0, 3, 0);
		gv->addEdge(1, 0, 4, 0);
		gv->addEdge(2, 3, 1, 0);
		gv->addEdge(3, 4, 2, 0);
		gv->addEdge(4, 2, 1, 0);
		gv->addEdge(5, 5, 1, 0);
		gv->addEdge(6, 6, 0, 0);
		gv->addEdge(7, 3, 4, 0);
		gv->addEdge(8, 1, 4, 0);
		gv->addEdge(9, 2, 3, 0);

		gv->setEdgeLabel(0, "100");
		gv->setEdgeLabel(1, "200");
		gv->setEdgeLabel(2, "100");
		gv->setEdgeLabel(3, "200");
		gv->setEdgeLabel(4, "400");
		gv->setEdgeLabel(5, "200");
		gv->setEdgeLabel(6, "300");
		gv->setEdgeLabel(7, "200");
		gv->setEdgeLabel(8, "100");
		gv->setEdgeLabel(9, "250");

		gv->rearrange();

		graph.floydWarshallShortestPath();
		graph.sortPaths();

		getchar();
}

void SupermarketNetwork::paintLoaded() {

	for (size_t i = 0; i < nodes.size(); i++) {
		fake_graph.addVertex(nodes[i], nodes[i].getType(), nodes[i].getNodeId());
		gv->addNode(nodes[i].getNodeId());
		if (nodes[i].getType() == "User"){

			gv->setVertexColor(nodes[i].getNodeId(), "yellow");

			stringstream str;

			str << nodes[i].getNodeId();

			gv->setVertexLabel(nodes[i].getNodeId(), str.str());
		}
		if (nodes[i].getType() == "Market"){
			gv->setVertexColor(nodes[i].getNodeId(), "green");

			stringstream str;

			str << nodes[i].getNodeId();

			gv->setVertexLabel(nodes[i].getNodeId(), str.str());
		}
	}

	for (size_t i = 0; i < edges.size(); i++) {
		if (edges[i].getEdgeId() != edges[i - 1].getEdgeId() && edges[i].getV1Id() != edges[i].getV2Id())
		{
			fake_graph.addEdge(edges[i].getV1Id(), edges[i].getV2Id(), 300.0);
			fake_graph.addEdge(edges[i].getV2Id(), edges[i].getV1Id(), 300.0);
			gv->addEdge(edges[i].getEdgeId(), edges[i].getV1Id(), edges[i].getV2Id(), 0);
		}
	}

	fake_graph.floydWarshallShortestPath();

	fake_graph.sortPaths();
}

void SupermarketNetwork::addSupermarket(std::string name) {
	/*graph.addVertex(Supermarket(name), "Supermarket");

	gv->addNode(marketId);

	//gv->setVertexLabel(marketId, name);

	gv->rearrange();

	marketId++;*/
}

bool SupermarketNetwork::handleRequest() {
	cout << "Choose a task" << endl << endl;

	cout << "Add" << endl;
	cout << "Exit" << endl << endl;

	cout << "Task: ";

	string operation;

	cin >> operation;

	if (operation == "Exit" || operation == "exit") {
		return false;
	}

	performOperation(operation);

	getchar();

	return true;
}

void SupermarketNetwork::performOperation(std::string operation) {
	if (operation == "Add") {
		string name;

		cout << "Name of the supermarket: ";

		cin >> name;

		addSupermarket(name);
	}
}

void SupermarketNetwork::loadMarkets() {
	ifstream inFile("Project-CAL/input/markets.txt");

	if (!inFile) {
		cerr << "Unable to open file markets.txt";
		exit(1);
	}

	string line;
	int id, x, y;

	while (!inFile.eof()) {
		getline(inFile, line);
		if (line == "")
			continue;
		stringstream linestream(line);
		string data;

		getline(linestream, data, ';');
		id = atoi(data.c_str());
		linestream >> x;
		getline(linestream, data, ';');
		linestream >> y;

		//cout << "Nome " << nome << " Valor " << valor << " Peso " << peso << " numero factura " << numfatura << " id destino" << id << endl;

		Supermarket s1(id, x, y);
		markets.push_back(s1);
	}
	inFile.close();
}

/** @brief Load nodes from nodes.txt to program */
void SupermarketNetwork::loadNodeInformation() {

	std::ifstream input_file("Project-CAL/input/nodes.txt");

	if (!input_file) {
		std::cerr << "Unable to open file nodes.txt";
		//return 1;
	}

	while (!input_file.eof()) {
		unsigned long long nodeID;
		double latitude, longitude;
		std::string line;
		std::string data;

		getline(input_file, line);
		std::stringstream input_stream(line);

		input_stream >> nodeID;
		getline(input_stream, data, ';');
		input_stream >> latitude;
		getline(input_stream, data, ';');
		input_stream >> longitude;

		/* Needs to be added to the database later */

		cout << "nodeID : " << nodeID << endl;
		cout << "latitude : " << latitude << endl;
		cout << "longitude : " << longitude << endl;

	}

	input_file.close();
}

void SupermarketNetwork::loadStreetInformation() {

	std::ifstream input_file("Project-CAL/input/streets.txt");

	if (!input_file) {
		std::cerr << "Unable to open file streets.txt";
		//return 1;
	}

	while (!input_file.eof()) {
		unsigned long long roadID;
		std::string roadName;
		bool isTwoWays;

		std::string line;
		std::string data;

		getline(input_file, line);
		std::stringstream input_stream(line);

		input_stream >> roadID;
		getline(input_stream, data, ';');
		getline(input_stream, data, ';');
		roadName = data;
		getline(input_stream, data, ';');

		if (data == "True")
			isTwoWays = true;
		else
			isTwoWays = false;

		/* Add to Street.cpp later to be added */

		cout << "roadID : " << roadID << endl;
		cout << "roadName : " << roadName << endl;
		cout << "isTwoWays : " << isTwoWays << endl << endl;

	}

	input_file.close();
}

void SupermarketNetwork::loadEdgeInformation() {
	std::ifstream input_file("Project-CAL/input/asd.txt");

	if (!input_file) {
		std::cerr << "Unable to open file edges.txt";
		//return 1;
	}

	while (!input_file.eof()) {
		unsigned long long roadID;
		unsigned long long nodeStartID;
		unsigned long long nodeEndID;
		std::string line;
		std::string data;

		getline(input_file, line);
		std::stringstream input_stream(line);

		input_stream >> roadID;
		getline(input_stream, data, ';');
		input_stream >> nodeStartID;
		getline(input_stream, data, ';');
		input_stream >> nodeEndID;

		/* Data needs to be saved */

		cout << "roadID : " << roadID << endl;
		cout << "nodeStartID : " << nodeStartID << endl;
		cout << "nodeEndID : " << nodeEndID << endl << endl;

	}

	input_file.close();
}

void SupermarketNetwork::loadNodesRandom() {
	std::ifstream input_file("Project-CAL/input/nodes_sandbox.txt");
	int rand_type;

	if (!input_file) {
		std::cerr << "Unable to open file nodes_sandbox.txt";
		//return 1;
	}

	while (!input_file.eof()) {
		rand_type = rand() % 3;
		string type;
		switch (rand_type) {
		case 0:
			type = "User";
			break;
		case 1:
			type = "Market";
			break;
		default:
			type = "Node";
		}
		long node_id;
		float lat_deg, long_deg, lat_rad, long_rad;
		std::string line;
		std::string data;

		getline(input_file, line);
		std::stringstream input_stream(line);

		input_stream >> node_id;
		getline(input_stream, data, ';');
		input_stream >> lat_deg;
		getline(input_stream, data, ';');
		input_stream >> long_deg;
		getline(input_stream, data, ';');
		input_stream >> long_rad;
		getline(input_stream, data, ' ');
		input_stream >> lat_deg;

		Node n1(node_id, type, lat_deg, long_deg, long_rad, lat_rad);
		nodes.push_back(n1);
		/* Data needs to be saved */

	}

	input_file.close();
}

void SupermarketNetwork::loadFakeEdges() {
	std::ifstream input_file("Project-CAL/input/edges_sandbox.txt");

	if (!input_file) {
		std::cerr << "Unable to open file edges_sandbox.txt";
		//return 1;
	}

	while (!input_file.eof()) {
		int edgeId, v1Id, v2Id;

		std::string line;
		std::string data;

		getline(input_file, line);
		std::stringstream input_stream(line);

		input_stream >> edgeId;
		getline(input_stream, data, ';');
		input_stream >> v1Id;
		getline(input_stream, data, ';');
		input_stream >> v2Id;

		/* Data needs to be saved */

		FakeEdge f1(edgeId, v1Id, v2Id);
		edges.push_back(f1);

	}

	input_file.close();
}
