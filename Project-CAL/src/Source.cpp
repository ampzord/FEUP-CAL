#include <iostream>
#include <sstream>
#include <fstream>

#include "Client.h"
#include "SupermarketNetwork.h"


int main() {

	SupermarketNetwork* sn = new SupermarketNetwork("ASD");
	sn->paintLoaded();

	//sn->loadEdgeInformation();
	//sn->manage();
	//sn->loadNodesRandom();

	//delete sn;
	getchar();

	return 0;
}

