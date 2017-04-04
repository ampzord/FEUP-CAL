#include <iostream>
#include <sstream>
#include <fstream>

#include "Client.h"
#include "SupermarketNetwork.h"

/**
 * \brief Cria uma SupermarketNetwork.
 * \details Aplica os algoritmos pretendidos,
 * \details Gera a vizualizacao do Grafo.
 */
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

