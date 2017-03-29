
#include <iostream>
#include <sstream>
#include <fstream>

#include "Client.h"
#include "SupermarketNetwork.h"

/** @brief Load clients from clients.txt to program */
void loadClients() {
    std::ifstream input_file("input/clients.txt");

    if (!input_file) {
        std::cerr << "Unable to open file clients.txt";
        //return 1;
    }

    std::string line;

    while (!input_file.eof()) {
        getline(input_file, line);
        std::stringstream input_stream(line);

        /* handle information */
    }
    input_file.close();
}

int main() {

    /*Client cli = Client("Antonio","Porto");
    std::cout << "Name : " << cli.getName() << " Address : " << cli.getAddress();*/

	SupermarketNetwork* sn = new SupermarketNetwork("ASD");

	sn->manage();

	delete sn;

    return 0;
}

