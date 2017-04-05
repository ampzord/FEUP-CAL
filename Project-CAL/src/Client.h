#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>

#include "Purchase.h"

/** \brief A client class that stores it's name, address and purchases. */

class Client {
private :
    std::string name;
    std::string address;
    std::vector<Purchase*> purchases;
public :

    /**
     * \brief Constructor for Client class with arguments.
     * \param name Name of the client.
     * \param address Address of the client. */
    Client(std::string name, std::string address);

    /** \brief Destroys a client. */
    ~Client() {};

    /** \brief Returns client name. */
    std::string getName();

    /**\brief Returns client address. */
    std::string getAddress();

    /** \brief  Returns client purchases. */
    std::vector<Purchase*> getPurchases() const;
};

#endif
