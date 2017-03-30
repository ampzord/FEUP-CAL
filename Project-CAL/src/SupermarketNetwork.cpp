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
	this->gv = new GraphViewer(600, 600, false);

	gv->createWindow(600, 600);

	gv->defineVertexColor("blue");

	gv->defineEdgeColor("black");

	loadMarkets();

	for (size_t i = 0; i < markets.size(); i++) {
		gv->addNode(markets[i].getId(), markets[i].getX(), markets[i].getY());
	}

	marketId = 0;
}

void SupermarketNetwork::manage() {
	while (handleRequest()) {
	}
}

void SupermarketNetwork::addSupermarket(std::string name) {
	graph.addVertex(Supermarket(name));

	gv->addNode(marketId);

	gv->setVertexLabel(marketId, name);

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
