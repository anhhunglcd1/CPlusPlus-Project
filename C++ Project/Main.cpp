#include <iostream>
#include "login_system.h"

int main()
{
	backupData();
	auto users = loadUsers();

	while (true)
	{
		cout << "=== SYSTEM ===\n"
			<< "1.Register\n"
			<< "2.Login\n"
			<< "0.Exit\n"
			<< "Select:";
		int cmd;
		cin >> cmd;
		if (cmd == 1)
		{
			registerUser(users);
		}
		else if (cmd == 2)
		{
			if (User* u = login(users))
			{
				if (u->isAdmin)
					adminMenu(u, users);
				else
					userMenu(u, users);
			}
		}
		else if (cmd == 0)
		{
			break;
		}
		else 
		{
			cout << "Invalid selection.\n";
		}

	}

	cout << "End.\n";
	return 0;
}