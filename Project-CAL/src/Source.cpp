
#include <iostream>
#include <sstream>
#include <fstream>

#include "Client.h"
#include "SupermarketNetwork.h"


int main() {
	SupermarketNetwork* sn = new SupermarketNetwork("ASD");

	//sn->loadEdgeInformation();

	sn->manage();

	delete sn;

    return 0;
}

