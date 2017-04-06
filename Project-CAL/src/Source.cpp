#include <iostream>
#include <sstream>
#include <fstream>

#include "SupermarketNetwork.h"

int main() {

	SupermarketNetwork* sn = new SupermarketNetwork("ASD");
	sn->mainMenu();
	//sn->paintLoaded();
	return 0;
}

