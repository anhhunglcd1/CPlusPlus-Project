#include "login_system.h"
#include <iostream>
#include <iomanip>
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
        cout << "\n=========================== USER MENU ============================\n";
        cout << left
            << setw(3) << "1." << setw(23) << "View Profile"
            << setw(3) << "2." << setw(23) << "Change Password"
            << setw(3) << "3." << "Change Name" << '\n'
            << setw(3) << "4." << setw(23) << "Transaction History"
            << setw(3) << "5." << setw(23) << "Transfer Points"
            << setw(3) << "0." << "Logout" << '\n';
        cout << string(66, '-') << "\n";
        cout << "Choice: ";
        int c; cin >> c;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (c) {
        case 1: viewProfile(u); break;
        case 2: changePassword(u, users); break;
        case 3: updateFullName(u, users); break;
        case 4: viewHistory(u); break;
        case 5: transferPoints(u, users); break;
        case 0: return;
        default: cout << "Invalid choice.\n";
        }
        pause();
    }
}

void adminMenu(User* u, vector<User>& users) {
    while (true) {
        clearScreen();
        cout << "\n=========================== ADMIN MENU ===========================\n";
        cout << left
            << setw(3) << "1." << setw(23) << "List Users"
            << setw(3) << "2." << setw(23) << "Create User"
            << setw(3) << "3." << "Edit User" << '\n'
            << setw(3) << "4." << setw(23) << "View User"
            << setw(3) << "5." << setw(23) << "Transfer Points"
            << setw(3) << "6." << "Delete User" << '\n'
            << setw(3) << "0." << "Logout" << '\n';
        cout << string(66, '-') << "\n";
        cout << "Choice: ";
        int c; cin >> c;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (c) {
        case 1:
            cout << "--- User List ---\n";
            for (auto& x : users)
                cout << x.username << (x.isAdmin ? " (Admin)" : "") << " - " << x.fullName << "\n";
            break;
        case 2: registerUser(users, false); break;
        case 3: {
            cout << "Username to edit: ";
            string nm; getline(cin, nm);
            User* v = findUser(users, nm);
            if (!v) { cout << "User not found.\n"; break; }

            cout << left
                << setw(4) << "1)" << setw(20) << "Change Full Name"
                << setw(4) << "2)" << setw(20) << "Change Password"
                << setw(4) << "0)" << "Exit" << '\n';
            cout << "Choice: ";
            int o; cin >> o; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (o == 1) scheduleFullNameChange(v, users);
            else if (o == 2) schedulePasswordChange(v, users);
            else if (o == 0) break;
            else cout << "Invalid choice.\n";
            break;
        }
        case 4: {
            cout << "Username to view: ";
            string nm; getline(cin, nm);
            User* v = findUser(users, nm);
            if (v) viewProfile(v);
            else cout << "User not found.\n";
            break;
        }
        case 5: transferPoints(u, users); break;
        case 6: {
            cout << "Username to delete: ";
            string nm; getline(cin, nm);
            if (nm == u->username) { cout << "Cannot delete yourself.\n"; break; }
            if (requireOTP(u->username)) {
                if (deleteUser(users, nm)) cout << "Deleted.\n";
                else cout << "User not found.\n";
            }
            break;
        }
        case 0: return;
        default: cout << "Invalid choice.\n";
        }
        pause();
    }
}
