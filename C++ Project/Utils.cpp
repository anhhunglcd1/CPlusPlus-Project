#include "login_system.h"
#include <random>     // Phát sinh số ngẫu nhiên
#include <sstream>    // Dùng ostringstream
#include <iomanip>    // Dùng setw, setfill
#include <cmath>      // Dùng pow
#include <cstdlib>    // system()
#include <iostream>   // In ra màn hình
#include <conio.h>    // _getch() (Windows)
using namespace std;

// ===== Sinh mật khẩu ngẫu nhiên =====
// length: độ dài mật khẩu (mặc định 8)
string genRandomPassword(int length) {
    // Tập ký tự cho phép: chữ hoa, chữ thường, số
    static const char chars[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789";
    random_device rd;
    mt19937 gen(rd());
    // Phân phối trên chỉ số mảng chars
    uniform_int_distribution<> dis(0, static_cast<int>(sizeof(chars) - 2));
    string s;
    s.reserve(length);
    for (int i = 0; i < length; ++i) {
        s += chars[dis(gen)];  // Chọn ngẫu nhiên ký tự
    }
    return s;
}

// ===== Sinh OTP =====
// digits: số chữ số OTP (mặc định 6)
string genOTP(int digits) {
    random_device rd;
    mt19937 gen(rd());
    // Phân phối số từ 0 đến 10^digits - 1
    uniform_int_distribution<> dis(0, static_cast<int>(pow(10, digits)) - 1);
    ostringstream ss;
    // Đảm bảo độ dài gồm digits chữ số, thêm số 0 phía trước nếu cần
    ss << setw(digits) << setfill('0') << dis(gen);
    return ss.str();
}

// ===== Hàm băm mật khẩu =====
// Sử dụng hash<string> của thư viện chuẩn
size_t hashPassword(const string& pwd) {
    return hash<string>{}(pwd);
}

// ===== Chuyển time_t thành chuỗi =====
// Định dạng: YYYY-MM-DD HH:MM:SS
string nowToString(time_t t) {
    struct tm lt {};
#ifdef _WIN32
    localtime_s(&lt, &t);  // Windows
#else
    localtime_r(&t, &lt);  // POSIX
#endif
    char buf[64] = { 0 };
    // strftime trả về số ký tự ghi vào buf
    if (strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &lt) > 0)
        return string(buf);
    return string("<invalid_time>");
}

// ===== Nhập mật khẩu ẩn ký tự =====
// Hiển thị '*' cho mỗi ký tự nhập
string inputHiddenPassword() {
    string password;
    char ch;
    while (true) {
        ch = _getch();  // Nhập ký tự mà không echo
        if (ch == 0 || ch == 224) {
            // Phím đặc biệt (mũi tên, function), bỏ qua ký tự kế tiếp
            (void)_getch();
            continue;
        }
        if (ch == '\r' || ch == '\n') {
            // Enter: kết thúc nhập
            cout << endl;
            break;
        }
        if (ch == 8 || ch == 127) {
            // Backspace: xóa ký tự cuối
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        }
        else {
            // Ký tự bình thường: lưu và hiển thị '*'
            password.push_back(ch);
            cout << '*';
        }
    }
    return password;
}

// ===== Xóa màn hình console =====
// Windows dùng cls, POSIX dùng clear
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
