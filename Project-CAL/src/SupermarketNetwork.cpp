#include "SupermarketNetwork.h"
#include "Node.h"
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;

SupermarketNetwork::SupermarketNetwork(std::string name) {
	this->name = name;
	this->gv = new GraphViewer(1000, 600, true);

	gv->createWindow(1000, 600);

	gv->defineVertexColor("blue");

	gv->defineEdgeColor("black");

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

void SupermarketNetwork::paintLoaded() {

	for (size_t i = 0; i < nodes.size(); i++) {
		bool res = fake_graph.addVertex(nodes[i], nodes[i].getType(),
				nodes[i].getNodeId());
		if (res)
			gv->addNode(nodes[i].getNodeId());
		else {
			continue;
		}
		if (nodes[i].getType() == "User") {

			gv->setVertexColor(nodes[i].getNodeId(), "yellow");

			stringstream str;

			str << nodes[i].getNodeId();

			gv->setVertexLabel(nodes[i].getNodeId(), str.str());
		}
		if (nodes[i].getType() == "Market") {
			gv->setVertexColor(nodes[i].getNodeId(), "green");

			stringstream str;

			str << nodes[i].getNodeId();

			gv->setVertexLabel(nodes[i].getNodeId(), str.str());
		}
	}

	for (size_t i = 0; i < edges.size(); i++) {
		if (edges[i].getEdgeId() != edges[i - 1].getEdgeId()
				&& edges[i].getV1Id() != edges[i].getV2Id()) {
			double lat1, lat2, long1, long2, distance;
			for (size_t j = 0; j < nodes.size(); j++) {
				if (nodes[j].getNodeId() == edges[i].getV1Id()) {
					lat1 = nodes[j].getLatitudeInDegrees();
					long1 = nodes[j].getLongitudeInDegrees();
				}
				if (nodes[j].getNodeId() == edges[i].getV2Id()) {
					lat2 = nodes[j].getLatitudeInDegrees();
					long2 = nodes[j].getLongitudeInDegrees();
				}
			}

			distance = distanceBetween2Nodes(lat1, lat2, long1, long2);
			bool res1, res2;

			if (edges[i].isTwoWay()) {
				res1 = fake_graph.addEdge(edges[i].getV1Id(),
						edges[i].getV2Id(), distance);
				res2 = fake_graph.addEdge(edges[i].getV2Id(),
						edges[i].getV1Id(), distance);
			} else {
				res1 = fake_graph.addEdge(edges[i].getV1Id(),
						edges[i].getV2Id(), distance);
				res2 = false;
			}
			if (res1 && res2) {
				gv->addEdge(edges[i].getEdgeId(), edges[i].getV1Id(),
						edges[i].getV2Id(), EdgeType::UNDIRECTED);
			} else if (res1) {
				gv->addEdge(edges[i].getEdgeId(), edges[i].getV1Id(),
						edges[i].getV2Id(), EdgeType::DIRECTED);
			}

			stringstream str;

			str << distance;

			gv->setEdgeLabel(edges[i].getEdgeId(), str.str());
		}
	}

	//fake_graph.cutNodes(gv);
	fake_graph.floydWarshallShortestPath();

	bool first = false;
	bool normal = true;

	if(first)
	{
		vector<pair<int, vector<int> > > res = fake_graph.sortPathsSingle(normal);
		printResults(res);
	}
	else
	{
		map<int, vector<int> > res = fake_graph.sortPaths(normal);
		printResults(res);
	}
}

void SupermarketNetwork::printResults(map<int, vector<int> > res) {
	ofstream myfile("Project-CAL/input/results.txt");
	if (myfile.is_open()) {
		for (map<int, vector<int> >::iterator it = res.begin(); it != res.end();
				it++) {
			myfile << "MARKET " << fake_graph.getVertexId(it->first) << endl;
			myfile << "PATH";
			cout << "MARKET " << fake_graph.getVertexId(it->first) << endl;
			cout << "PATH";
			for (unsigned int i = 0; i < it->second.size(); i++) {
				myfile << " " << fake_graph.getVertexId(it->second[i]);
			}
			for (unsigned int i = 0; i < it->second.size(); i++) {
				cout << " " << fake_graph.getVertexId(it->second[i]);
			}

			cout << endl << endl;
			myfile << endl << "<----------------------->" << endl;
		}

		myfile.close();
	}
}

void SupermarketNetwork::printResults(vector<pair<int, vector<int> > > res) {
	ofstream myfile("Project-CAL/input/results.txt");
	if (myfile.is_open()) {
		for (vector<pair<int, vector<int> > >::iterator it = res.begin(); it != res.end();
				it++) {
			myfile << "MARKET " << fake_graph.getVertexId(it->first) << endl;
			myfile << "PATH";
			cout << "MARKET " << fake_graph.getVertexId(it->first) << endl;
			cout << "PATH";
			for (unsigned int i = 0; i < it->second.size(); i++) {
				myfile << " " << fake_graph.getVertexId(it->second[i]);
			}
			for (unsigned int i = 0; i < it->second.size(); i++) {
				cout << " " << fake_graph.getVertexId(it->second[i]);
			}

			cout << endl << endl;
			myfile << endl << "<----------------------->" << endl;
		}

		myfile.close();
	}
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

void SupermarketNetwork::loadStreetInformation() {

	std::ifstream input_file("Project-CAL/input/streets5.txt");

	if (!input_file) {
		std::cerr << "Unable to open file streets.txt";
		exit(1);
	}

	while (!input_file.eof()) {
		unsigned long long roadID;
		FakeEdge * f1;
		int pos;

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

		if (isEdgePosById(roadID)) {
			pos = getEdgePosById(roadID);
			edges[pos].setTwoWay(isTwoWays);
		}

	}

	input_file.close();
}

void SupermarketNetwork::loadEdgeInformation() {
	std::ifstream input_file("Project-CAL/input/edges5.txt");

	if (!input_file) {
		std::cerr << "Unable to open file edges.txt";
		exit(1);
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

		FakeEdge f1(roadID, nodeStartID, nodeEndID);
		edges.push_back(f1);
	}

	input_file.close();
}

void SupermarketNetwork::loadNodesRandom() {
	std::ifstream input_file("Project-CAL/input/nodes5.txt");
	srand(time(NULL));
	int rand_type;

	if (!input_file) {
		std::cerr << "Unable to open file nodes.txt";
		exit(1);
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
		unsigned long long node_id;
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
		input_stream >> lat_rad;

		Node n1(node_id, type, lat_deg, long_deg, long_rad, lat_rad);
		nodes.push_back(n1);
	}

	input_file.close();
}

double SupermarketNetwork::distanceBetween2Nodes(double lat1, double lat2,
		double long1, double long2) {
	double R = 6371000;

	double lat1_rad = lat1 * PI / 180;
	double lat2_rad = lat2 * PI / 180;

	double deltaLat = (lat2 - lat1) * PI / 180;
	double deltaLong = (long2 - long1) * PI / 180;

	double a = sin(deltaLat / 2) * sin(deltaLat / 2)
															+ cos(lat1_rad) * cos(lat2_rad) * sin(deltaLong / 2)
															* sin(deltaLong / 2);
	double c = 2 * atan2(sqrt(a), sqrt(1 - a));

	return R * c;
}

int SupermarketNetwork::getEdgePosById(unsigned long long id) {
	int pos = 0;

	for (size_t i = 0; i < edges.size(); i++) {
		if (edges[i].getEdgeId() == id)
			return i;
	}
}

bool SupermarketNetwork::isEdgePosById(unsigned long long id) {
	for (size_t i = 0; i < edges.size(); i++) {
		if (edges[i].getEdgeId() == id)
			return true;
	}
	return false;
}

void SupermarketNetwork::mainMenu() {
	bool run = true;

	while(run)
	{
		int opt = -1;

		do {
			cout << "WELCOME TO SUPERMARKET HOME DELIVERY SYSTEM" << endl << endl;
			cout << "1 - Graph from openstreetmaps.org text files." << endl;
			cout << "2 - Simple graph." << endl;
			cout << "0 - Leave" << endl;

			cin.clear();
			cin >> opt;

		} while (opt < 0 || opt > 2);

		switch (opt) {
		case 1:
			loadInformationOpenStreetMapsGraph();
			chooseAlgorithmFromOpenStreetMapsGraph();
			paintLoaded();
			break;
		case 2:
			chooseAlgorithmFromSimpleGraph();
			break;
		case 0:
			run = false;
			break;
		default:
			break;
		}
	}
}

void SupermarketNetwork::chooseAlgorithmFromOpenStreetMapsGraph() {
	bool run = true;

	while(run)
	{
		int opt = -1;

		do {
			cout << "Choose algorithm you want to use:" << endl << endl;
			cout << "1 - Single Market Approach with extremities." << endl;
			cout << "2 - Multiple Markets Approach with extremities." << endl;
			cout << "3 - Single Market Approach." << endl;
			cout << "4 - Multiple Markets Approach." << endl;
			cout << "0 - Go Back." << endl;
			cin.clear();
			cin >> opt;

		} while (opt < 0 || opt > 4);

		run = false;

		switch (opt) {
		case 1:
			fake_graph.sortPathsSingle(true);
			break;
		case 2:
			fake_graph.sortPaths(true);
			break;
		case 3:
			fake_graph.sortPathsSingle(false);
			break;
		case 4 :
			fake_graph.sortPaths(false);
			break;
		case 0:
			mainMenu();
			break;
		default:
			break;
		}
	}
}

void SupermarketNetwork::chooseAlgorithmFromSimpleGraph() {
	bool run = true;

	while(run)
	{
		int opt = -1;

		do {
			cout << "Choose algorithm you want to use:" << endl << endl;
			cout << "1 - Single Market Approach with extremities." << endl;
			cout << "2 - Multiple Markets Approach with extremities." << endl;
			cout << "3 - Single Market Approach." << endl;
			cout << "4 - Multiple Markets Approach." << endl;
			cout << "0 - Go Back." << endl;
			cin.clear();
			cin >> opt;

		} while (opt < 0 || opt > 4);

		switch (opt) {
		case 1:
			fake_graph.sortPathsSingle(true);
			break;
		case 2:
			fake_graph.sortPaths(true);
			break;
		case 3:
			fake_graph.sortPathsSingle(false);
			break;
		case 4 :
			fake_graph.sortPaths(false);
			break;
		case 0:
			run = false;
			mainMenu();
			break;
		default:
			break;
		}
	}

}

void SupermarketNetwork::loadInformationOpenStreetMapsGraph() {
	loadNodesRandom();
	loadEdgeInformation();
	loadStreetInformation();
}
