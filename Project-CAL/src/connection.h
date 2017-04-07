#ifndef _CONNECTION_
#define _CONNECTION_

#include <cstdio>
#include <cstdlib>
#include <cstring>

#ifdef linux
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#else
#include <winsock2.h>
#endif

#include <string>
#include <iostream>

using namespace std;

/** \brief Class used to handle Clienter-Server connection. */
class Connection {
public:
	/** brief Builds a connection, with the given conection port.
	 * \param port Port used for the connection.
	 */
	Connection(short port);

	/** \brief Sends a message to the given socket's port.
	 * \param port Socket's Port to send te message.
	 */
	bool sendMsg(string msg);

	/** \brief Read a message from the given Socket's Port.
	 */
	string readLine();
private:
#ifdef linux
	int sock;
#else
	SOCKET sock;
#endif
};

#endif
