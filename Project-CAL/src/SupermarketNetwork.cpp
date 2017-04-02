/*
 * SupermarketNetwork.cpp
 *
 *  Created on: 29/03/2017
 *      Author: furys
 */

#include "SupermarketNetwork.h"
#include "Supermarket.h"
#include <fstream>
#include <sstream>

using namespace std;

SupermarketNetwork::SupermarketNetwork(std::string name) {
	// TODO Auto-generated constructor stub

	this->name = name;
	this->gv = new GraphViewer(600, 600, true);

	gv->createWindow(600, 600);

	gv->defineVertexColor("blue");

	gv->defineEdgeColor("black");

	//loadMarkets();

	/*for (size_t i = 0; i < markets.size(); i++) {
		gv->addNode(markets[i].getId(), markets[i].getX(), markets[i].getY());
	}*/

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

	graph.addVertex(x, "Supermarket");

	graph.addVertex(y, "Client");
	graph.addVertex(z, "Client");

	graph.addVertex(w, "Nothing");
	graph.addVertex(u, "Nothing");
	graph.addVertex(i, "Supermarket");
	graph.addVertex(a, "Client");

	graph.addEdge(x, w, 5);
	graph.addEdge(w, x, 5);

	graph.addEdge(x, u, 8);
	graph.addEdge(u, x, 8);

	graph.addEdge(w, y, 2);
	graph.addEdge(y, w, 2);

	graph.addEdge(u, z, 3);
	graph.addEdge(z, u, 3);

	graph.addEdge(z, y, 4);
	graph.addEdge(y, z, 4);

	graph.addEdge(i, y, 10);
	graph.addEdge(y, i, 10);

	graph.addEdge(a, x, 2);
	graph.addEdge(x, a, 2);

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

	gv->setEdgeLabel(0, "5");
	gv->setEdgeLabel(1, "8");
	gv->setEdgeLabel(2, "2");
	gv->setEdgeLabel(3, "3");
	gv->setEdgeLabel(4, "4");
	gv->setEdgeLabel(5, "10");
	gv->setEdgeLabel(6, "2");

	gv->rearrange();

	graph.floydWarshallShortestPath();
	graph.sortPaths();

	getchar();
}

void SupermarketNetwork::addSupermarket(std::string name) {
	graph.addVertex(Supermarket(name), "Supermarket");

	gv->addNode(marketId);

	//gv->setVertexLabel(marketId, name);

	gv->rearrange();

	marketId++;
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
