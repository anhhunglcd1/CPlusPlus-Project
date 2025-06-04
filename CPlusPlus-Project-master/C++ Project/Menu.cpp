#include "login_system.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

// Hàm tạm dừng màn hình, chờ người dùng nhấn Enter để tiếp tục
static void pause() {
    cout << "\nPress Enter to continue...";
    while (cin.rdbuf()->in_avail() > 0) {
        char c = cin.peek();
        if (c == '\n') {
            cin.get();
            break;
        }
        cin.get();
    }
    cin.get();
}


// Menu chức năng dành cho user thông thường (không phải admin)
// Thực hiện theo lựa chọn của người dùng: xem profile, đổi mật khẩu, đổi tên, xem lịch sử, chuyển điểm...
void userMenu(User* u, vector<User>& users) {
    while (true) {
        clearScreen(); // Xóa màn hình cho giao diện gọn đẹp
        cout << "\n=========================== USER MENU ============================\n";
        cout << left
            << setw(3) << "1." << setw(23) << "View Profile"         // Xem thông tin cá nhân
            << setw(3) << "2." << setw(23) << "Change Password"      // Đổi mật khẩu
            << setw(3) << "3." << "Change Name" << '\n'              // Đổi tên
            << setw(3) << "4." << setw(23) << "Transaction History"  // Xem lịch sử giao dịch ví
            << setw(3) << "5." << setw(23) << "Transfer Points"      // Chuyển điểm cho user khác
            << setw(3) << "0." << "Logout" << '\n';                  // Đăng xuất
        cout << string(66, '-') << "\n";
        cout << "Choice: ";
        int c; cin >> c;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa ký tự thừa sau nhập số
        switch (c) {
        case 1: viewProfile(u); break;           // Xem profile
        case 2: changePassword(u, users); break; // Đổi mật khẩu
        case 3: updateFullName(u, users); break; // Đổi tên
        case 4: viewHistory(u); break;           // Xem lịch sử giao dịch
        case 5: transferPoints(u, users); break; // Chuyển điểm
        case 0: return;                          // Đăng xuất, thoát menu user
        default: cout << "Invalid choice.\n";    // Nhập sai lựa chọn
        }
        pause(); // Chờ nhấn Enter trước khi quay lại menu
    }
}

// Menu chức năng dành cho admin
// Có thể: xem danh sách user, tạo user, chỉnh sửa user, xem profile user, chuyển điểm, xóa user...
void adminMenu(User* u, vector<User>& users) {
    while (true) {
        clearScreen(); // Xóa màn hình cho giao diện gọn đẹp
        cout << "\n=========================== ADMIN MENU ===========================\n";
        cout << left
            << setw(3) << "1." << setw(23) << "List Users"          // Hiển thị danh sách tất cả user
            << setw(3) << "2." << setw(23) << "Create User"         // Tạo user mới (admin tạo hộ)
            << setw(3) << "3." << "Edit User" << '\n'               // Sửa thông tin user (đổi tên/mật khẩu)
            << setw(3) << "4." << setw(23) << "View User"           // Xem thông tin chi tiết 1 user
            << setw(3) << "5." << setw(23) << "Transfer Points"     // Chuyển điểm từ admin
            << setw(3) << "6." << "Delete User" << '\n'             // Xóa user
            << setw(3) << "7." << "View Reward Pool" << '\n'        // Xem số điểm còn lại trong pool
            << setw(3) << "0." << "Logout" << '\n';                 // Đăng xuất
        cout << string(66, '-') << "\n";
        cout << "Choice: ";
        int c; cin >> c;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (c) {
        case 1: // Hiển thị danh sách user
            cout << "--- User List ---\n";
            for (auto& x : users)
                cout << x.username << (x.isAdmin ? " (Admin)" : "") << " - " << x.fullName << "\n";
            break;
        case 2: // Tạo user mới (admin tạo hộ)
            registerUser(users, false);
            break;
        case 3: { // Sửa thông tin user
            cout << "\n--- Current Users ---\n";
            for (auto& x : users) {
                cout << "  • " << x.username
                    << (x.isAdmin ? " (Admin)" : "")
                    << " - " << x.fullName << "\n";
            }
            cout << "---------------------\n";
            cout << "Username to edit: ";
            string nm; getline(cin, nm);
            User* v = findUser(users, nm);
            if (!v) { cout << "User not found.\n"; break; }
            // Chọn sửa tên hoặc đổi mật khẩu
            cout << left
                << setw(4) << "1)" << setw(20) << "Change Full Name"
                << setw(4) << "2)" << setw(20) << "Change Password"
                << setw(4) << "0)" << "Exit" << '\n';
            cout << "Choice: ";
            int o; cin >> o; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (o == 1) scheduleFullNameChange(v, users); // Đổi tên (cần xác nhận OTP từ user)
            else if (o == 2) schedulePasswordChange(v, users); // Đổi mật khẩu (cần xác nhận OTP từ user)
            else if (o == 0) break;
            else cout << "Invalid choice.\n";
            break;
        }
        case 4: { // Xem thông tin 1 user cụ thể
            cout << "\n--- Current Users ---\n";
            for (auto& x : users) {
                cout << "  • " << x.username
                    << (x.isAdmin ? " (Admin)" : "")
                    << " - " << x.fullName << "\n";
            }
            cout << "---------------------\n";
            cout << "Username to view: ";
            if (cin.peek() == '\n') cin.get();
            string nm; getline(cin, nm);
            User* v = findUser(users, nm);
            if (v) viewProfile(v);
            else cout << "User not found.\n";
            break;
        }
        case 5: // Chuyển điểm từ tài khoản 
            transferPoints(u, users);
            break;
        case 6: { // Xóa user (không xóa chính mình)
            cout << "\n--- Current Users ---\n";
            for (auto& x : users) {
                if (!x.isAdmin) {
                    cout << "  • " << x.username << "\n";
                }
            }
            cout << "----------------------\n";
            cout << "Username to delete: ";
            string uname;
            User* target = nullptr;
            while (true) {
                cout << "Enter username to delete: ";
                cin >> uname;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // hút newline dư nếu sau này dùng getline

                // Kiểm tra xem uname có tồn tại trong danh sách users không
                target = nullptr;
                for (auto& x : users) {
                    if (x.username == uname) {
                        target = &x;
                        break;
                    }
                }
                if (!target) {
                    cout << "Username \"" << uname << "\" not found. Please try again.\n\n";
                }
                else {
                    break;  // tìm thấy rồi thì thoát vòng while
                }
            }
            if (uname == u->username) { cout << "Cannot delete yourself.\n"; break; }
            if (requireOTP(u->username)) { // Xác nhận OTP trước khi xóa
                if (deleteUser(users, uname)) cout << "Deleted.\n";
                else cout << "User not found.\n";
            }
            break;
        }
        case 7: { // Xem số điểm còn lại trong reward pool
            cout << "\nCurrent reward pool has " << rewardPool << " points remaining.\n";
            break;
        }
        case 0: return; // Đăng xuất, thoát menu admin
        default: cout << "Invalid choice.\n"; // Nhập sai lựa chọn
        }
        pause(); // Chờ nhấn Enter trước khi quay lại menu
    }
}
