
#include <iostream>

#include "Client.h"
#include "Supermarket.h

int main() {
    Client cli = Client("Antonio","Porto");
    printf("Name : %s , Address : %s", cli.getName(), cli.getAddress());

    return 0;
}

