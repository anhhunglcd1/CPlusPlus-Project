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
        cout << "1. View Profile  2. Change Password  3. Update Name\n";
        cout << "4. Transaction History  5. Transfer Points  0. Logout\n";
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
        cout << "1. List Users  2. Create User  3. Edit User\n";
        cout << "4. View User  5. Transfer Points  6. Delete User  0. Logout\n";
        cout << "Choice: ";
        int c; cin >> c;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (c) {
        case 1:
            cout << "--- User List ---\n";
            for (auto& x : users)
                cout << x.username << (x.isAdmin ? " (Admin)" : "") << " - " << x.fullName << "\n";
            break;
            // Đổi từ registerAdmin(users) -> registerUser(users, false)
        case 2: registerUser(users, false); break; // Sửa tại đây!
        case 3: {
            cout << "Username to edit: ";
            string nm; getline(cin, nm);
            User* v = findUser(users, nm);
            if (!v) { cout << "User not found.\n"; break; }
            cout << "1) Change Full Name  2) Change Password\nChoice: ";
            int o; cin >> o; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (o == 1) scheduleFullNameChange(v, users);
            else if (o == 2) schedulePasswordChange(v, users);
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
