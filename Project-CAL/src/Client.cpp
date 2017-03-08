#include "Client.h"

Client::Client(std::string name, std::string address) {
    this->name = name;
    this->address = address;
}

std::string Client::getName() {
    return name;
}

std::string Client::getAddress() {
    return address;
}
