#include <iostream>
#include <sstream>
#include <fstream>

#include "Client.h"
#include "SupermarketNetwork.h"


int main() {
	SupermarketNetwork* sn = new SupermarketNetwork("ASD");

	//sn->loadEdgeInformation();
	//sn->manage();
	//sn->loadNodesRandom();
	sn->paintLoaded();
	//delete sn;
	getchar();

	return 0;
}

