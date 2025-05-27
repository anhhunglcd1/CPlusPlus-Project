#include "login_system.h"
#include <iostream>
#include <limits>
using namespace std;

static void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void userMenu(User* u, vector<User>& users) {
    while (true) {
        clearScreen();
        cout << "\n"
            << "1. View Profile        2. Change Password\n"
            << "3. Update Name         4. Transaction History\n"
            << "5. Transfer Points     0. Logout\n"
            << "Choice: ";
        int c;
        cin >> c;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (c) {
        case 1: viewProfile(u);            break;
        case 2: changePassword(u, users);  break;
        case 3: updateFullName(u, users);  break;
        case 4: viewHistory(u);            break;
        case 5: transferPoints(u, users);  break;
        case 0: return;
        default: cout << "Invalid choice.\n"; break;
        }
        pause();
    }
}

void adminMenu(User* u, vector<User>& users) {
    while (true) {
        clearScreen();
        cout << "\n"
            << "1. List Users          2. Create Admin\n"
            << "3. Edit User           4. View User Info\n"
            << "5. Transfer Points     6. Delete User\n"
            << "0. Logout\n"
            << "Choice: ";
        int c;
        cin >> c;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (c) {
        case 1:
            cout << "\n--- User List ---\n";
            for (const auto& x : users)
                cout << x.username
                << (x.isAdmin ? " (Admin)" : "")
                << " - " << x.fullName << "\n";
            break;
        case 2:
            registerAdmin(users);
            break;
        case 3: {
            cout << "Username to edit: ";
            string nm;
            getline(cin, nm);
            if (User* v = findUser(users, nm))
                updateFullName(v, users);
            else
                cout << "User not found.\n";
            break;
        }
        case 4: {
            cout << "Username to view: ";
            string nm;
            getline(cin, nm);
            if (User* v = findUser(users, nm))
                viewProfile(v);
            else
                cout << "User not found.\n";
            break;
        }
        case 5:
            transferPoints(u, users);
            break;
        case 6: {
            cout << "Username to delete: ";
            string nm;
            getline(cin, nm);
            if (nm == u->username) {
                cout << "Cannot delete yourself.\n";
            }
            else if (requireOTP(u->username)) {
                if (deleteUser(users, nm))
                    cout << "User \"" << nm << "\" deleted.\n";
                else
                    cout << "User not found.\n";
            }
            break;
        }
        case 0:
            return;
        default:
            cout << "Invalid choice.\n";
        }
        pause();
    }
}
