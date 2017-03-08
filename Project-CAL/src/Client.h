#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client {
private :
    std::string name;
    std::string address;
public :
    Client(std::string name, std::string address);
    std::string getName();
    std::string getAddress();
};

#endif
