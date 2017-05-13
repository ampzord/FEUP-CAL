#include "SupermarketNetwork.h"
#include "Node.h"
#include <fstream>
#include <sstream>
#include <ctime>
#include <string>
#include <iostream>

using namespace std;

SupermarketNetwork::SupermarketNetwork(std::string name) {
	this->name = name;
	this->gv = new GraphViewer(1280, 720, true);

	gv->createWindow(1280, 720);

	gv->defineVertexColor("blue");

	gv->defineEdgeColor("black");

	marketId = 0;
}

void SupermarketNetwork::paintLoaded() {

	for (size_t i = 0; i < nodes.size(); i++) {
		bool res = fake_graph.addVertex(nodes[i], nodes[i].getType(),
				nodes[i].getNodeId(), nodes[i].getName());
		if (res)
			gv->addNode(nodes[i].getNodeId());
		else {
			continue;
		}
		if (nodes[i].getType() == "User") {

			gv->setVertexColor(nodes[i].getNodeId(), "yellow");

			stringstream str;

			str << nodes[i].getNodeId();

			gv->setVertexLabel(nodes[i].getNodeId(), "");
		}
		if (nodes[i].getType() == "Market") {
			gv->setVertexColor(nodes[i].getNodeId(), "green");

			stringstream str;

			str << nodes[i].getNodeId();

			gv->setVertexLabel(nodes[i].getNodeId(), nodes[i].getName());
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
						edges[i].getV2Id(), distance, edges[i].getName());
				res2 = fake_graph.addEdge(edges[i].getV2Id(),
						edges[i].getV1Id(), distance, edges[i].getName());
			} else {
				res1 = fake_graph.addEdge(edges[i].getV1Id(),
						edges[i].getV2Id(), distance, edges[i].getName());
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

			gv->setEdgeLabel(edges[i].getEdgeId(), edges[i].getName());
		}
	}

	fake_graph.floydWarshallShortestPath();

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

void SupermarketNetwork::loadStreetInformation() {

	std::ifstream input_file("Project-CAL/input/streets6.txt");

	if (!input_file) {
		std::cerr << "Unable to open file streets.txt";
		exit(1);
	}

	while (!input_file.eof()) {
		unsigned long long roadID;
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
			edges[pos].setName(roadName);
		}

	}

	input_file.close();
}

void SupermarketNetwork::loadEdgeInformation() {
	std::ifstream input_file("Project-CAL/input/edges6.txt");

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
	std::ifstream input_file("Project-CAL/input/nodes6.txt");
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
			cout << "0 - Leave" << endl;

			cin.clear();
			cin >> opt;

		} while (opt < 0 || opt > 1);

		run = false;

		switch (opt) {
		case 1:
			loadInformationOpenStreetMapsGraph();
			paintLoaded();
			chooseOption();
			break;
		case 0:
			exit(0);
			break;
		default:
			break;
		}
	}
}

void getUserInput(string &input) {
	cout << "Name of street/supermarket :" << endl;
	if (!(cin >> input)) {
		cin.clear();
		cin.ignore(10000,'\n');
	}
}

void SupermarketNetwork::chooseOption() {

	int opt = -1;
	cout << endl;

	do {
		cout << "Choose an option:" << endl << endl;
		cout << "1 - Single Market Approach with extremities." << endl;
		cout << "2 - Multiple Markets Approach with extremities." << endl;
		cout << "3 - Single Market Approach with shortest path." << endl;
		cout << "4 - Multiple Markets Approach with shortest path." << endl;
		cout << "5 - Find exact name of street/supermarket." << endl;
		cout << "6 - Find approximated name of street/supermarket." << endl;
		cout << "0 - Go Back." << endl;
		cin.clear();
		cin >> opt;

	} while (opt < 0 || opt > 6);

	switch (opt) {
	case 1:
	{
		vector<pair<int, vector<int> > > res1 = fake_graph.sortPathsSingle(true);
		printResults(res1);
		break;
	}
	case 2:
	{
		map<int, vector<int> > res2 = fake_graph.sortPaths(true);
		printResults(res2);
		break;
	}
	case 3:
	{
		vector<pair<int, vector<int> > > res3 = fake_graph.sortPathsSingle(false);
		printResults(res3);
		break;
	}
	case 4 :
	{
		map<int, vector<int> > res4 = fake_graph.sortPaths(false);
		printResults(res4);
		break;
	}
	case 5 :
	{
			//input
			int size;
			cout << "How many roads:" << endl;

			cin >> size;

			vector<string> roads;

			getchar();

			for(int i = 0; i < size; i++)
			{
				string road;

				cout << "Road number " << i + 1 << " name:"<< endl;

				getline(cin,road);
				roads.push_back(road);
			}

			cout << "Market name:" << endl;

			string market;

			getline(cin, market);

			cout << fake_graph.exactSearch(roads, market) << endl;

			//search
			//result
			break;
	}
	case 6 :
	{
			//input
			//string userInput;
			//getUserInput(userInput);
			//cout << "Input:" << userInput << endl;
			//search
			//result
			break;
	}
	case 0:
	{
		mainMenu();
		break;
	}
	default:
	{
		break;
	}
	}
}

void SupermarketNetwork::loadInformationOpenStreetMapsGraph() {
	loadNodesRandom();
	loadEdgeInformation();
	loadStreetInformation();
}

int GetMilliCount()
{
	timeb tb;
	ftime( &tb );
	int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
	return nCount;
}

int GetMilliSpan(int nTimeStart)
{
	int nSpan = GetMilliCount() - nTimeStart;
	if (nSpan < 0)
		nSpan += 0x100000 * 1000;
	return nSpan;
}

void SupermarketNetwork::runTime() {
	ofstream myfile("Project-CAL/input/time.txt");
	if (myfile.is_open()) {

		//		myfile << "Single Market Approach with extremities" << endl;
		//
		//		int nTimeStart = GetMilliCount();
		//		vector<pair<int, vector<int> > > res1 = fake_graph.sortPathsSingle(true);
		//		int nTimeElapsed = GetMilliSpan( nTimeStart );
		//		printResults(res1);
		//		myfile << nTimeElapsed << " milliseconds" << endl << endl;

		myfile << "Multiple Markets Approach with extremities" << endl;

		int nTimeStart = GetMilliCount();
		map<int, vector<int> > res2 = fake_graph.sortPaths(true);
		int nTimeElapsed = GetMilliSpan( nTimeStart );
		printResults(res2);
		myfile << nTimeElapsed << " milliseconds" << endl << endl;

		myfile << "Single Market Approach." << endl;

		nTimeStart = GetMilliCount();
		vector<pair<int, vector<int> > > res3 = fake_graph.sortPathsSingle(false);
		nTimeElapsed = GetMilliSpan( nTimeStart );
		printResults(res3);
		myfile << nTimeElapsed << " milliseconds" << endl << endl;

		myfile << "Multiple Markets Approach." << endl;

		nTimeStart = GetMilliCount();
		map<int, vector<int> > res4 = fake_graph.sortPaths(false);
		nTimeElapsed = GetMilliSpan( nTimeStart );
		printResults(res4);
		myfile << nTimeElapsed << " milliseconds" << endl << endl;

		myfile.close();
	}
}
