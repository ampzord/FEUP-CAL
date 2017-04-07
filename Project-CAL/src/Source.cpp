#include <iostream>
#include <sstream>
#include <fstream>

#include "SupermarketNetwork.h"

int main() {

	SupermarketNetwork* sn = new SupermarketNetwork("Home Delivery System");
	sn->mainMenu();
	getchar();
	getchar();
	return 0;
}

