#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>

#include "Purchase.h"

class Client {
private :
    std::string name;
    std::string address;
    std::vector<Purchase*> purchases;
public :
    Client(std::string name, std::string address);
    ~Client() {};
    std::string getName();
    std::string getAddress();
    std::vector<Purchase*> getPurchases() const;
};

#endif
