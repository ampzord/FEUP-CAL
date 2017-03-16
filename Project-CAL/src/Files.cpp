#include "Files.h"

void Files::loadDatabase()
{
	std::ifstream users("users.txt"), groups("groups.txt"),
		userMessages("userMessages.txt"), groupMessages("groupMessages.txt"), waitingMessages("waitingMessages.txt");

	// temporary storage vectors
	std::vector<User *> u;
	std::vector<Group *> g;
	std::vector<Message <User> *> mu;
	std::vector<Message <Group> *> mg;
	std::vector<Message<Group> *> wm;

	// load files
	if (users.is_open())
		loadUsers(users, u);
	else
		std::cerr << "'users.txt' not opened.\n";

	if (groups.is_open())
		loadGroups(groups, g, u);
	else
		std::cerr << "'groups.txt' not opened.\n";

	if (userMessages.is_open())
		loadUserMessages(userMessages, mu, u);
	else
		std::cerr << "'userMessages.txt' not opened.\n";

	if (groupMessages.is_open())
		loadGroupMessages(groupMessages, mg, g, u);
	else
		std::cerr << "'groupMessages.txt' not opened.\n";

	if (waitingMessages.is_open())
		loadGroupMessages(waitingMessages, wm, g, u);
	else
		std::cerr << "'waitingMessages.txt' not opened. \n";

	// sort vectors
	if (u.size() > 0)
		Algorithm<User>::QuickSort(u, 0, (int)u.size() - 1);
	if (g.size() > 0)
		Algorithm<Group>::QuickSort(g, 0, (int)g.size() - 1);
	if (mu.size() > 0)
		Algorithm<Message <User> >::QuickSort(mu, 0, (int)mu.size() - 1);
	if (mg.size() > 0)
		Algorithm<Message <Group> >::QuickSort(mg, 0, (int)mg.size() - 1);


	std::vector<Group *> g2 = g;

	// load to users them groups
	for (unsigned int i = 0; i < u.size(); i++)
	{
		for (unsigned int j = 0; j < g.size(); j++)
		{
			if (g[j]->getModeratorUser() == u[i])
				u[i]->addGroup(g[j]);
			else
			{
				bool stop = false;
				for (unsigned int k = 0; k < g[j]->getGroupUsersInfo().size() && !stop; k++)
					if (g[j]->getGroupUsersInfo()[k]->getUser() == u[i]) {
						u[i]->addGroup(g[j]);
						stop = true;
					}
			}
		}
	}

	// load conversations to them users
	std::vector<std::vector<Message <User> *> > mbc; // messages by conversation between users
	for (unsigned int i = 0; i < mu.size(); i++)
	{
		// we use two 'for' cycles to the 'if' do not become messy
		int index = -1;
		for (unsigned int j = 0; j < mbc.size() && index == -1; j++)
			if ((mbc[j][0]->getSender() == mu[i]->getSender()) && (mbc[j][0]->getReceiver() == mu[i]->getReceiver()))
				index = j;

		if (index == -1)
			for (unsigned int j = 0; j < mbc.size() && index == -1; j++)
				if ((mbc[j][0]->getSender() == mu[i]->getReceiver()) && (mbc[j][0]->getReceiver() == mu[i]->getSender()))
					index = j;

		if (index > -1)
			mbc[index].push_back(mu[i]);
		else
		{
			std::vector<Message <User> *> newConversation;
			newConversation.push_back(mu[i]);
			mbc.push_back(newConversation);
		}
	}

	for (unsigned int i = 0; i < mbc.size(); i++)
	{
		int senderPos = Algorithm<User>::binarySearch(u, mbc[i][0]->getSender());
		int receiverPos = Algorithm<User>::binarySearch(u, mbc[i][0]->getReceiver());

		Conversation<User> *c = new Conversation<User>(mbc[i]);
		u[senderPos]->addConversation(c);
		u[receiverPos]->addConversation(c);
	}

	// load conversations to them groups
	for (unsigned int i = 0; i < g.size(); i++)
	{
		std::vector<Message <Group> *> messages;

		for (unsigned int j = 0; j < mg.size(); j++)
			if (mg[j]->getReceiver() == g[i])
				messages.push_back(mg[j]);

		if (messages.size() > 0) {
			Conversation<Group> *c = new Conversation<Group>(messages);
			g[i]->changeConversation(c);
		}
	}

	//load messages to priority queue
	for (unsigned int i = 0; i < g2.size(); i++)
	{
		std::vector<Message <Group> *> messages2;

		for (unsigned int j = 0; j < wm.size(); j++)
		{
			if (wm[j]->getReceiver() == g2[i])
			{
				if (wm[j]->getSender() != g2[i]->getModeratorUser())
					messages2.push_back(wm[j]);
			}
		}
		for (size_t k = 0; k < messages2.size(); k++)
			g2[i]->AddToPriority_queue(messages2[k]);
	}

	users.close();
	groups.close();
	userMessages.close();
	groupMessages.close();
	waitingMessages.close();

	User::checkIfInactiveUser_AddToHash();

	std::cout << "Database load completed.\n";
	system("pause");
}

//-------------------------------------------------------------------------

void Files::storeDatabase()
{
	std::ofstream users("users.txt"), groups("groups.txt"),
		userMessages("userMessages.txt"), groupMessages("groupMessages.txt"), waitingMessages("waitingMessages.txt");

	std::vector<User *> u = User::getUsers();
	std::vector<Group *> g = Group::getSetOfGroups();

	storeUsersToFile(users, u);
	storeGroupsToFile(groups, g);

	/* store messages from each user, but as the pointers are repeated (both the sender
	as the receiver have the same pointer) it is necessary to remove the repeated ones */
	std::vector<Message <User> *> mu;
	for (unsigned int i = 0; i < u.size(); i++)
	{
		std::vector<Conversation <User> *> conversations = u[i]->getConversations();
		for (unsigned int j = 0; j < conversations.size(); j++)
		{
			std::vector<Message <User> *> messages = conversations[j]->getMessages();
			for (unsigned int k = 0; k < messages.size(); k++)
				if (messages[k]->getSender() == u[i])	// only store the sender version, the receiver version is the same
					mu.push_back(messages[k]);
		}
	}
	storeUserMessagesToFile(userMessages, mu);

	// store validated messages from each group because them pointers are not repeated
	for (unsigned int i = 0; i < g.size(); i++)
		storeGroupMessagesToFile(groupMessages, g[i]->getConversation()->getMessages());

	// store not validated messages from each group because them pointers are not repeated
	for (unsigned int i = 0; i < g.size(); i++)
		storeGroupWaitingMessagesToFile(waitingMessages, g[i]->getPriorityqueue());


	users.close();
	groups.close();
	userMessages.close();
	groupMessages.close();
	waitingMessages.close();

	std::cout << "Database storage completed.\n";
	system("pause");
}

//-------------------------------------------------------------------------

void Files::loadUsers(std::ifstream &in, std::vector<User *> &u)
{
	while (!in.eof())
	{
		std::string line_str;
		getline(in, line_str);

		if (line_str.length() > 0)
		{
			// differentiate date in its components
			for (unsigned int i = 0; i < line_str.length(); i++)
				if (line_str[i] == '/' || line_str[i] == ':')
					line_str[i] = ' ';

			// store all of the components in a vector
			std::vector<std::string> strings(10);	// login, name, email, cellphone, year, month, day, hour, minute, second
			for (unsigned int i = 0, j = 0; i < line_str.length(); i++)
			{
				if (line_str[i] == ' ')
					j++;	// next component
				else
					strings[j] += line_str[i];
			}

			// convert some strings to integers
			std::vector<int> date(6); // year, month, day, hour, minute, second;
			for (unsigned int i = 4; i < 10; i++)
			{
				std::stringstream valueOfDate(strings[i]);
				valueOfDate >> date[i - 4];
			}

			Date *d = NULL;
			User *user = NULL;
			try {
				d = new Date(date[0], date[1], date[2], date[3], date[4], date[5]);
				user = new User(strings[0], strings[1], strings[2], strings[3], d);
				u.push_back(user);
			}
			catch (Date::InvalidDate) { std::cerr << "Indication that the date is invalid: " << strings[0] << ".\n"; }
			catch (User::CellphoneAlreadyExists &c) { delete(d);  std::cerr << "Indication that the cellphone already exists: " << c.getCellphone() << ".\n"; }
			catch (User::EmailAlreadyExists &e) { delete(d);  std::cerr << "Indication that the email already exists: " << e.getEmail() << ".\n"; }
			catch (User::UserAlreadyExists &u) { delete(d);   std::cerr << "Indication that the user already exists: " << u.getLogin() << ".\n"; }
			catch (...)
			{
				delete(d);
				delete(user);
				std::cerr << "Problem loading user sign up date or user: " << strings[0] << ".\n";
			}
		}
	}
}

//-------------------------------------------------------------------------

std::ofstream& Files::storeUsersToFile(std::ofstream &out, const std::vector<User *> u)
{
	for (unsigned int i = 0; i < u.size(); i++)
	{
		out << u[i]->getLogin() << " " << u[i]->getName() << " "
			<< u[i]->getEmail() << " " << u[i]->getCellphone() << " "
			<< u[i]->getDate() << std::endl;
	}

	return out;
}

//-------------------------------------------------------------------------

void Files::loadGroups(std::ifstream &in, std::vector<Group *> &g, std::vector<User *> &u)
{
	while (!in.eof())
	{
		std::string line_str;
		getline(in, line_str);

		if (line_str.length() > 0)
		{
			// differentiate date in its components
			for (unsigned int i = 0; i < line_str.length(); i++)
				if (line_str[i] == '/' || line_str[i] == ':')
					line_str[i] = ' ';

			// store all of the components in a vector
			std::vector<std::string> strings(1);	// title, year, month, day, hour, minute, second, privateGroup, moderatorLogin, moderatorName, std::vector<User *>;
			for (unsigned int i = 0, j = 0; i < line_str.length(); i++)
			{
				if (line_str[i] == ' ') {
					j++;	// next component
					strings.push_back("");
				}
				else
					strings[j] += line_str[i];
			}

			// convert some strings to integers
			std::vector<int> date(6); // year, month, day, hour, minute, second;
			for (unsigned int i = 1; i < 7; i++)
			{
				std::stringstream valueOfDate(strings[i]);
				valueOfDate >> date[i - 1];
			}
			Date *d = NULL;
			try { d = new Date(date[0], date[1], date[2], date[3], date[4], date[5]); }
			catch (Date::InvalidDate) { std::cerr << "Problem loading group creation date: " << strings[0] << ".\n"; }
			catch (...)
			{
				delete(d);
				std::cerr << "Problem loading group creation date: " << strings[0] << ".\n";
			}

			bool privateGroup;
			std::stringstream prvGroup(strings[7]);
			prvGroup >> privateGroup;

			User *moderator = NULL;
			for (unsigned int i = 0; i < u.size() && moderator == NULL; i++)
				if (u[i]->getLogin() == strings[8] && u[i]->getName() == strings[9])
					moderator = u[i];

			std::vector<User *> users;
			for (unsigned int i = 10; i < strings.size(); i++)
			{
				bool stop = false;
				for (unsigned int j = 0; j < u.size() && !stop; j++)
					if (strings[i] == u[j]->getLogin()) {
						users.push_back(u[j]);
						stop = true;
					}
			}

			try {
				Group *group = new Group(strings[0], d, privateGroup, moderator, users);
				g.push_back(group);
			}
			catch (Group::ExistingTitle &t) { std::cerr << "Problem loading group (existing title): " << t.getTitle() << ".\n"; }
			catch (...) { std::cerr << "Problem loading group: " << strings[0] << ".\n"; }
		}
	}
}

//-------------------------------------------------------------------------

std::ofstream& Files::storeGroupsToFile(std::ofstream &out, const std::vector<Group *> g)
{
	for (unsigned int i = 0; i < g.size(); i++)
	{
		out << g[i]->getTitle() << " " << g[i]->getGroupCreationDate() << " "
			<< g[i]->getPrivateGroup() << " " << g[i]->getModeratorUser()->getLogin()
			<< " " << g[i]->getModeratorUser()->getName();

		for (unsigned int j = 0; j < g[i]->getGroupUsersInfo().size(); j++)
			out << " " << g[i]->getGroupUsersInfo()[j]->getUser()->getLogin();

		out << std::endl;
	}

	return out;
}

//-------------------------------------------------------------------------

void Files::loadUserMessages(std::ifstream &in, std::vector<Message<User> *> &mu, std::vector<User *> &u)
{
	while (!in.eof())
	{
		std::string line_str;
		getline(in, line_str);

		if (line_str.length() > 0)
		{
			// differentiate date in its components
			for (unsigned int i = 0; i < line_str.length(); i++)
				if (line_str[i] == '/' || line_str[i] == ':')
					line_str[i] = ' ';

			// store all of the components in a vector
			/* strings: year, month, day, hour, minute, second, senderLogin, receiverLogin, messageContent */
			std::vector<std::string> strings(9);
			for (unsigned int i = 0, j = 0; i < line_str.length(); i++)
			{
				if (line_str[i] == ' ' && j != 8)	// j != position of the messageContent
					j++;	// next component
				else
					strings[j] += line_str[i];
			}

			// convert some strings to integers
			std::vector<int> date(6); // year, month, day, hour, minute, second;
			for (unsigned int i = 0; i < 6; i++)
			{
				std::stringstream valueOfDate(strings[i]);
				valueOfDate >> date[i];
			}

			User *sender = NULL;
			User *receiver = NULL;
			for (unsigned int i = 0; (i < u.size()) && (sender == NULL || receiver == NULL); i++)
			{
				// search sender
				if (u[i]->getLogin() == strings[6])
					sender = u[i];
				else
					// search receiver
					if (u[i]->getLogin() == strings[7])
						receiver = u[i];
			}

			Date *d = NULL;
			try { d = new Date(date[0], date[1], date[2], date[3], date[4], date[5]); }
			catch (Date::InvalidDate) { std::cerr << "Problem loading the date of a user message: " << strings[8] << ".\n"; }
			catch (...) { std::cerr << "Problem loading the date of a user message: " << strings[8] << ".\n"; }

			if (strings[8] == "Image Message") {
				Image_Message<User> *message = new Image_Message<User>(d, sender, receiver);
				mu.push_back(message);
			}
			else
				if (strings[8] == "Video Message") {
					Video_Message<User> *message = new Video_Message<User>(d, sender, receiver);
					mu.push_back(message);
				}
				else {
					Text_Message<User> *message = new Text_Message<User>(d, sender, receiver, strings[8]);
					mu.push_back(message);
				}
		}
	}
}

//-------------------------------------------------------------------------

std::ofstream& Files::storeUserMessagesToFile(std::ofstream &out, const std::vector<Message <User> *> mu)
{
	for (unsigned int i = 0; i < mu.size(); i++)
		out << mu[i]->getDate() << " " << mu[i]->getSender()->getLogin() << " "
		<< mu[i]->getReceiver()->getLogin() << " " << mu[i]->getMessageContent() << "\n";

	return out;
}

//-------------------------------------------------------------------------

void Files::loadGroupMessages(std::ifstream &in, std::vector<Message<Group> *> &mg, std::vector<Group *> &g, std::vector<User *> &u)
{
	while (!in.eof())
	{
		std::string line_str;
		getline(in, line_str);

		if (line_str.length() > 0)
		{
			// differentiate date in its components
			for (unsigned int i = 0; i < line_str.length(); i++)
				if (line_str[i] == '/' || line_str[i] == ':')
					line_str[i] = ' ';

			// store all of the components in a vector
			/* strings: year, month, day, hour, minute, second, senderLogin, receiverTitle, messageContent */
			std::vector<std::string> strings(9);
			for (unsigned int i = 0, j = 0; i < line_str.length(); i++)
			{
				if (line_str[i] == ' ' && j != 8) // j != position of the messageContent
					j++;	// next component
				else
					strings[j] += line_str[i];
			}

			// convert some strings to integers
			std::vector<int> date(6); // year, month, day, hour, minute, second;
			for (unsigned int i = 0; i < 6; i++)
			{
				std::stringstream valueOfDate(strings[i]);
				valueOfDate >> date[i];
			}

			User *sender = NULL;
			Group *receiver = NULL;
			for (unsigned int i = 0; i < u.size() && sender == NULL; i++)
			{
				// search sender
				if (u[i]->getLogin() == strings[6])
					sender = u[i];
			}
			for (unsigned int i = 0; i < g.size() && receiver == NULL; i++)
			{
				// search receiver
				if (g[i]->getTitle() == strings[7])
					receiver = g[i];
			}

			Date *d = NULL;
			try { d = new Date(date[0], date[1], date[2], date[3], date[4], date[5]); }
			catch (Date::InvalidDate) { std::cerr << "Problem loading the date of a group message: " << strings[8] << ".\n"; }
			catch (...) { std::cerr << "Problem loading the date of a group message: " << strings[8] << ".\n"; }

			if (strings[8] == "Image Message") {
				Image_Message<Group> *message = new Image_Message<Group>(d, sender, receiver);
				mg.push_back(message);
			}
			else
				if (strings[8] == "Video Message") {
					Video_Message<Group> *message = new Video_Message<Group>(d, sender, receiver);
					mg.push_back(message);
				}
				else {
					Text_Message<Group> *message = new Text_Message<Group>(d, sender, receiver, strings[8]);
					mg.push_back(message);
				}
		}
	}
}

//-------------------------------------------------------------------------

std::ofstream& Files::storeGroupMessagesToFile(std::ofstream &out, const std::vector<Message <Group> *> mg)
{
	for (unsigned int i = 0; i < mg.size(); i++)
		out << mg[i]->getDate() << " " << mg[i]->getSender()->getLogin() << " "
		<< mg[i]->getReceiver()->getTitle() << " " << mg[i]->getMessageContent() << "\n";

	return out;
}

//-------------------------------------------------------------------------

std::ofstream & Files::storeGroupWaitingMessagesToFile(std::ofstream &out, const std::priority_queue< MessagePoint<Group> > &heap)
{
	std::priority_queue< MessagePoint<Group> > wm = heap;	// wm = waiting messages
	while (!wm.empty())
	{
		Message<Group> *m = wm.top().getMessagePoint();
		out << m->getDate() << " " << m->getSender()->getLogin() << " "
			<< m->getReceiver()->getTitle() << " " << m->getMessageContent() << "\n";

		wm.pop();
	}

	return out;
}
