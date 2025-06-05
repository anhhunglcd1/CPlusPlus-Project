#include "login_system.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

// =========================
// Hàm tạm dừng màn hình
// =========================
// Dùng sau khi xử lý xong 1 chức năng để người dùng kịp đọc kết quả trước khi về menu
static void pause() {
    cout << "\nPress Enter to continue...";
    // Làm sạch buffer nhập nếu còn ký tự thừa (tránh bị trôi màn hình)
    while (cin.rdbuf()->in_avail() > 0) {
        char c = cin.peek();
        if (c == '\n') {
            cin.get();
            break;
        }
        cin.get();
    }
    cin.get(); // Đợi người dùng nhấn Enter thật sự mới tiếp tục
}

// =========================
// USER MENU
// =========================
// Menu chính cho người dùng bình thường (không phải admin)
// Cho phép xem thông tin cá nhân, đổi mật khẩu/tên, xem lịch sử giao dịch, chuyển điểm, hoặc đăng xuất
void userMenu(User* u, vector<User>& users) {
    while (true) {
        clearScreen(); // Dọn màn hình cho giao diện gọn, không bị rối sau mỗi thao tác
        cout << "\n=========================== USER MENU ============================\n";
        // In danh sách lựa chọn (số thứ tự và mô tả chức năng)
        cout << left
            << setw(3) << "1." << setw(23) << "View Profile"         // Xem thông tin tài khoản
            << setw(3) << "2." << setw(23) << "Change Password"      // Đổi mật khẩu đăng nhập
            << setw(3) << "3." << "Change Name" << '\n'              // Đổi tên hiển thị
            << setw(3) << "4." << setw(23) << "Transaction History"  // Xem lịch sử chuyển/nhận điểm
            << setw(3) << "5." << setw(23) << "Transfer Points"      // Chuyển điểm cho người khác
            << setw(3) << "0." << "Logout" << '\n';                  // Đăng xuất
        cout << string(66, '-') << "\n";
        cout << "Choice: ";
        int c;
        // Nhận lựa chọn và kiểm tra lỗi nhập (chỉ nhận số)
        if (!(cin >> c)) {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear(); // Xóa trạng thái lỗi nhập
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa các ký tự thừa trong buffer
            pause(); // Chờ nhấn Enter trước khi quay lại menu
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Loại bỏ Enter thừa

        // Xử lý lựa chọn tương ứng
        switch (c) {
        case 1: viewProfile(u); break;           // Xem thông tin cá nhân
        case 2: changePassword(u, users); break; // Đổi mật khẩu (phải xác thực OTP)
        case 3: updateFullName(u, users); break; // Đổi tên (phải xác thực OTP)
        case 4: viewHistory(u); break;           // Xem lịch sử giao dịch ví
        case 5: transferPoints(u, users); break; // Chuyển điểm cho user khác
        case 0: return;                          // Thoát menu -> quay lại menu chính (logout)
        default: cout << "Invalid choice.\n";    // Nếu nhập sai lựa chọn
        }
        pause(); // Dừng lại chờ nhấn Enter để user kịp đọc kết quả thao tác trước khi quay lại menu
    }
}

// =========================
// ADMIN MENU
// =========================
// Menu chính cho tài khoản admin
// Được phép quản lý toàn bộ hệ thống: danh sách user, tạo/sửa/xem/xóa user, chuyển điểm, kiểm tra pool
void adminMenu(User* u, vector<User>& users) {
    while (true) {
        clearScreen(); // Dọn màn hình cho gọn
        cout << "\n=========================== ADMIN MENU ===========================\n";
        // In các lựa chọn chức năng dành riêng cho admin
        cout << left
            << setw(3) << "1." << setw(23) << "List Users"          // Xem toàn bộ danh sách user
            << setw(3) << "2." << setw(23) << "Create User"         // Tạo mới user (admin tạo hộ)
            << setw(3) << "3." << "Edit User" << '\n'               // Sửa thông tin user (tên hoặc mật khẩu)
            << setw(3) << "4." << setw(23) << "View User"           // Xem chi tiết một user cụ thể
            << setw(3) << "5." << setw(23) << "Transfer Points"     // Admin chuyển điểm cho user khác
            << setw(3) << "6." << "Delete User" << '\n'             // Xóa tài khoản user (không xóa admin)
            << setw(3) << "7." << "View Reward Pool" << '\n'        // Xem số điểm thưởng còn lại trong hệ thống
            << setw(3) << "0." << "Logout" << '\n';                 // Đăng xuất khỏi menu admin
        cout << string(66, '-') << "\n";
        cout << "Choice: ";
        int c;
        // Nhận lựa chọn, kiểm tra hợp lệ (chỉ nhận số)
        if (!(cin >> c)) {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pause();
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Loại bỏ Enter thừa

        // Xử lý từng chức năng
        switch (c) {
        case 1: // Hiển thị danh sách tất cả user (bao gồm cả admin)
            cout << "--- User List ---\n";
            for (auto& x : users)
                cout << x.username << (x.isAdmin ? " (Admin)" : "") << " - " << x.fullName << "\n";
            break;
        case 2: // Tạo mới user (admin thao tác), tham số byAdmin = false
            registerUser(users, false);
            break;
        case 3: { // Chỉnh sửa thông tin user (chọn user -> đổi tên hoặc đổi mật khẩu)
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
            // Menu nhỏ chọn sửa tên hay sửa mật khẩu
            cout << left
                << setw(4) << "1)" << setw(20) << "Change Full Name"
                << setw(4) << "2)" << setw(20) << "Change Password"
                << setw(4) << "0)" << "Exit" << '\n';
            cout << "Choice: ";
            int o; cin >> o; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (o == 1) scheduleFullNameChange(v, users);       // Đặt lịch đổi tên (user xác nhận OTP ở lần đăng nhập)
            else if (o == 2) schedulePasswordChange(v, users);  // Đặt lịch đổi mật khẩu (user xác nhận OTP)
            else if (o == 0) break;
            else cout << "Invalid choice.\n";
            break;
        }
        case 4: { // Xem chi tiết một user cụ thể
            cout << "\n--- Current Users ---\n";
            for (auto& x : users) {
                cout << "  • " << x.username
                    << (x.isAdmin ? " (Admin)" : "")
                    << " - " << x.fullName << "\n";
            }
            cout << "---------------------\n";
            cout << "Username to view: ";
            if (cin.peek() == '\n') cin.get();  // Nếu Enter bị dư từ trước thì loại bỏ
            string nm; getline(cin, nm);
            User* v = findUser(users, nm);
            if (v) viewProfile(v);
            else cout << "User not found.\n";
            break;
        }
        case 5: // Admin chuyển điểm cho user khác (admin không bị trừ điểm)
            transferPoints(u, users);
            break;
        case 6: { // Xóa user (không xóa chính mình, không xóa admin)
            cout << "\n--- Current Users ---\n";
            // Liệt kê danh sách user thường (không phải admin)
            for (auto& x : users) {
                if (!x.isAdmin) {
                    cout << "  • " << x.username << "\n";
                }
            }
            cout << "----------------------\n";
            string uname;
            User* target = nullptr;
            // Vòng lặp để nhập username cần xóa, cho nhập lại nếu sai
            while (true) {
                cout << "Enter username to delete (or 0 to cancel): ";
                getline(cin, uname); // Nhập username muốn xóa (hoặc nhập 0 để hủy)
                if (uname == "0") { // Nếu nhập 0 thì hủy thao tác xóa
                    cout << "Cancel delete user.\n";
                    break; // Thoát vòng lặp, không xóa
                }
                target = nullptr;
                // Tìm user theo username (và phải là user thường, không phải admin)
                for (auto& x : users) {
                    if (x.username == uname && !x.isAdmin) {
                        target = &x; // Nếu tìm được, lưu con trỏ tới user đó
                        break;
                    }
                }
                if (!target) {
                    // Không tìm thấy user hợp lệ
                    cout << "Username \"" << uname << "\" not found, please try again.\n";
                }
                else if (uname == u->username) {
                    // Không cho phép tự xóa chính mình
                    cout << "Cannot delete yourself.\n";
                }
                else {
                    // Đúng username của user thường, không phải admin, không phải chính mình
                    if (requireOTP(u->username)) { // Xác nhận OTP trước khi xóa
                        if (deleteUser(users, uname)) cout << "Deleted.\n"; // Xóa thành công
                        else cout << "Delete failed.\n"; // Có lỗi khi xóa
                    }
                    break; // Dù xóa thành công hay không, đều thoát vòng lặp
                }
            }
            break;
        }

        case 7: // Xem số điểm còn lại trong reward pool của hệ thống
            cout << "\nCurrent reward pool has " << rewardPool << " points remaining.\n";
            break;
        case 0: return; // Đăng xuất, thoát khỏi menu admin
        default: cout << "Invalid choice.\n";
        }
        pause(); // Dừng lại, chờ nhấn Enter trước khi quay lại menu
    }
}
