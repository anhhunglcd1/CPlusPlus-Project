#include "login_system.h"
#include <iostream>
#include <limits>    // Dùng numeric_limits
using namespace std;

// ===== Hàm tạm dừng màn hình =====
// Hiển thị thông báo và chờ người dùng nhấn Enter
static void pause() {
    cout << "\nPress Enter to continue...";
    // Xóa các ký tự còn lại trong buffer trước khi đợi Enter
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// ===== Menu cho người dùng thường =====
// Hiển thị các chức năng: xem profile, đổi mật khẩu, cập nhật tên,
// xem lịch sử giao dịch, chuyển điểm, và đăng xuất
void userMenu(User* u, vector<User>& users) {
    while (true) {
        clearScreen();  // Xóa màn hình để hiển thị menu mới
        cout << "\n"
            << "1. View Profile        2. Change Password\n"
            << "3. Update Name         4. Transaction History\n"
            << "5. Transfer Points     0. Logout\n"
            << "Choice: ";
        int c;
        cin >> c;
        // Kiểm tra nếu nhập không phải số
        if (cin.fail()) {
            cout << "Invalid choice. Please enter a number.\n";
            cin.clear();  // Reset lỗi
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pause();
            continue;    // Quay lại menu
        }
        // Xóa newline còn sót
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (c) {
        case 1:
            viewProfile(u);           // Hiển thị thông tin cá nhân
            break;
        case 2:
            changePassword(u, users); // Thay đổi mật khẩu
            break;
        case 3:
            updateFullName(u, users); // Cập nhật họ tên
            break;
        case 4:
            viewHistory(u);           // Xem lịch sử giao dịch
            break;
        case 5:
            transferPoints(u, users);// Chuyển điểm cho người khác
            break;
        case 0:
            return;                   // Đăng xuất, thoát menu
        default:
            cout << "Invalid choice.\n";
        }
        pause();  // Đợi người dùng nhấn Enter trước khi làm mới menu
    }
}

// ===== Menu cho Admin =====
// Cho phép: liệt kê user, tạo admin, sửa user, xem info user,
// chuyển điểm, xóa user, và đăng xuất
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
        if (cin.fail()) {
            cout << "Invalid choice. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pause();
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (c) {
        case 1: {
            // Liệt kê danh sách tất cả users
            cout << "\n--- User List ---\n";
            for (const auto& x : users) {
                cout << x.username
                    << (x.isAdmin ? " (Admin)" : "")
                    << " - " << x.fullName << "\n";
            }
            break;
        }
        case 2:
            registerAdmin(users);  // Tạo thêm admin
            break;
        case 3: {
            // Sửa thông tin (chỉ cập nhật họ tên)
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
            // Xem chi tiết user khác
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
            transferPoints(u, users);  // Admin chuyển điểm
            break;
        case 6: {
            // Xóa user, với OTP xác thực và tránh tự xóa chính mình
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
            return;  // Đăng xuất khỏi admin menu
        default:
            cout << "Invalid choice.\n";
        }
        pause();  // Đợi Enter trước khi làm mới menu
    }
}
