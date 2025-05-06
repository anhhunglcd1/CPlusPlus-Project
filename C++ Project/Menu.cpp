#include "login_system.h"
#include <iostream>

void userMenu(User* u, vector<User>& users) {
    while (true) {
        cout << "\n1.View information\n"
            << "\n2.Change password\n"
            << "\n3.Rename\n"
            << "\n4.History\n"
            << "\n5.Transfer points\n"
            << "\n0.Log out\n"
            << "\nSelect: \n";
        int c; cin >> c;
        switch (c) {
        case 1: viewProfile(u); break;
        case 2: changePassword(u, users); break;
        case 3: updateFullName(u, users); break;
        case 4: viewHistory(u); break;
        case 5: transferPoints(u, users); break;
        case 0: return;
        default: cout << "Invalid selection.\n";
        }
    }
}

void adminMenu(User* u, vector<User>& users) {
    while (true) {
        cout << "\n1.Danh sách user\n"
            << "\n2.Create user\n"
            << "\n3.Edit user\n"
            << "\n0.Đăng xuất\n"
            << "Chọn: \n";
        int c; cin >> c;
        if (c == 1) {
            cout << "--- LIST ---\n";
            for (auto& x : users)
                cout << x.username << (x.isAdmin ? "(A)" : "") << " - " << x.fullName << "\n";
        }
        else if (c == 2) {
            registerUser(users, true);
        }
        else if (c == 3) {
            cout << "Username to be edited: "; string nm; cin >> nm;
            if (User* v = findUser(users, nm))
                updateFullName(v, users);
            else
                cout << "User not found.\n";
        }
        else if (c == 0) {
            return;
        }
        else {
            cout << "Invalid selection.\n";
        }
    }
}
