#ifndef FILES_H
#define FILES_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

/** @brief A files class that loads/stores the information to in files to the program */

class Files
{
public:
	/** @brief Loads all the database */
	static void loadDatabase();
	/** @brief Stores all the database */
	static void storeDatabase();

	/** @brief Loads the users file to a vector of pointers to users
	 * @param in A stream to the file with the users
	 * @param u A empty vector of pointers to users that will store the users
	 * obtained from the file */
	static void loadUsers(std::ifstream &in, std::vector<User *> &u);
	/** @brief Stores the users from a vector of pointers to users
	 * @param out A stream to the file that will contain the users
	 * @param u A vector of pointers to users that are to store in the file */
	static std::ofstream& storeUsersToFile(std::ofstream &out, const std::vector<User *> u);

	/** @brief Loads the groups file to a vector of pointers to groups
	 * @param in A stream to the file with the groups
	 * @param g A empty vector of pointers to groups that will store the groups
	 * obtained from the file
	 * @param u A vector of pointers to users that will help to store the groups
	 * obtained from the file */
	static void loadGroups(std::ifstream &in, std::vector<Group *> &g, std::vector<User *> &u);
	/** @brief Stores the groups from a vector of pointers to groups
	 * @param out A stream to the file that will contain the groups
	 * @param g A vector of pointers to groups that are to store in the file */
	static std::ofstream& storeGroupsToFile(std::ofstream &out, const std::vector<Group *> g);

	/** @brief Loads the user messages file to a vector of pointers to user messages
	 * @param in A stream to the file with the user messages
	 * @param mu A empty vector of pointers to user messages that will store the
	 * user messages obtained from the file
	 * @param u A vector of pointers to users that will help to store the messages
	 * obtained from the file */
	static void loadUserMessages(std::ifstream &in, std::vector<Message<User> *> &mu, std::vector<User *> &u);
	/** @brief Stores the user messages from a vector of pointers to user messages
	 * @param out A stream to the file that will contain the user messages
	 * @param mu A vector of pointers to user messages that are to store in the file */
	static std::ofstream& storeUserMessagesToFile(std::ofstream &out, const std::vector<Message <User> *> mu);

	/** @brief Loads the group messages file to a vector of pointers to group messages
	 * @param in A stream to the file with the group messages
	 * @param mg A empty vector of pointers to group messages that will store the
	 * group messages obtained from the file
	 * @param g A vector of pointers to groups that will help to store the messages
	 * obtained from the file
	 * @param u A vector of pointers to users that will help to store the messages
	 * obtained from the file */
	static void loadGroupMessages(std::ifstream &in, std::vector<Message<Group> *> &mg, std::vector<Group *> &g, std::vector<User *> &u);
	/** @brief Stores the group messages from a vector of pointers to group messages
	 * @param out A stream to the file that will contain the group messages
	 * @param mg A vector of pointers to group messages that are to store in the file */
	static std::ofstream& storeGroupMessagesToFile(std::ofstream &out, const std::vector<Message <Group> *> mg);
	/** @brief Stores the group waiting messages that need validation from a priority queue of MessagePoint
	* @param out A stream to the file that will contain the group waiting messages
	* @param heap A priority queue of MessagePoint that are to store in the file */
	static std::ofstream& storeGroupWaitingMessagesToFile(std::ofstream &out, const std::priority_queue< MessagePoint<Group> > &heap);
};

#endif