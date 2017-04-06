#include <iostream>
#include <sstream>
#include <fstream>

#include "SupermarketNetwork.h"

int main() {

	SupermarketNetwork* sn = new SupermarketNetwork("ASD");
	sn->loadInformationOpenStreetMapsGraph();
	sn->paintLoaded();
	//sn->mainMenu();
	//sn->test();
	sn->runTime();
	getchar();
	return 0;
}

