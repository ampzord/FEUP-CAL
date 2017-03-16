#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client {
private :
    std::string name;
    std::string address;
public :
    Client(std::string name, std::string address);
    ~Client() {};
    std::string getName();
    std::string getAddress();
};

#endif
