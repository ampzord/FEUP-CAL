#include "Client.h"

Client::Client(std::string name, std::string address) {
    this->name = name;
    this->address = address;
}

Client::getName() {
    return name;
}

Client::getAddress() {
    return address;
}
