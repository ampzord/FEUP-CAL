/*
 * SupermarketNetwork.cpp
 *
 *  Created on: 29/03/2017
 *      Author: furys
 */

#include "SupermarketNetwork.h"

using namespace std;

SupermarketNetwork::SupermarketNetwork(std::string name) {
	// TODO Auto-generated constructor stub

	this->name = name;
	this->gv = new GraphViewer(600, 600, true);

	gv->createWindow(600, 600);

	gv->defineVertexColor("blue");

	gv->defineEdgeColor("black");

	marketId = 0;
}

void SupermarketNetwork::manage()
{
	while(handleRequest()) {}
}

void SupermarketNetwork::addSupermarket(std::string name)
{
	graph.addVertex(Supermarket(name));

	gv->addNode(marketId);

	gv->setVertexLabel(marketId, name);

	gv->rearrange();

	marketId++;
}

bool SupermarketNetwork::handleRequest()
{
	cout << "Choose a task" << endl << endl;

	cout << "Add" << endl;
	cout << "Exit" << endl << endl;;

	cout << "Task: ";

	string operation;

	cin >> operation;

	if(operation == "Exit" || operation == "exit")
	{
		return false;
	}

	performOperation(operation);

	getchar();

	return true;
}

void SupermarketNetwork::performOperation(std::string operation)
{
	if(operation == "Add")
	{
		string name;

		cout << "Name of the supermarket: ";

		cin >> name;

		addSupermarket(name);
	}
}
