#include "login_system.h"
#include <random>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <iostream>
#ifdef _WIN32
#include <conio.h>
#endif
using namespace std;

// Sinh mật khẩu ngẫu nhiên độ dài length (chứa chữ hoa, chữ thường, số)
// Trả về: chuỗi mật khẩu ngẫu nhiên
string genRandomPassword(int length) {
    static const char chars[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789"; // Tập ký tự cho phép
    random_device rd;             // Thiết bị sinh số ngẫu nhiên
    mt19937 gen(rd());            // Bộ sinh số ngẫu nhiên chuẩn Mersenne Twister
    uniform_int_distribution<> dis(0, sizeof(chars) - 2); // Phân phối đều từ 0 đến cuối mảng
    string s;
    for (int i = 0; i < length; ++i)
        s += chars[dis(gen)];     // Chọn ngẫu nhiên từng ký tự và thêm vào chuỗi
    return s;
}

// Sinh mã OTP ngẫu nhiên có số chữ số là digits (mặc định 6)
// Trả về: chuỗi OTP (chỉ chứa số, có độ dài digits, đủ số 0 ở đầu nếu cần)
string genOTP(int digits) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, static_cast<int>(pow(10, digits)) - 1); // Sinh số ngẫu nhiên theo số chữ số mong muốn
    ostringstream ss;
    ss << setw(digits) << setfill('0') << dis(gen); // Bổ sung số 0 đầu nếu cần
    return ss.str();
}

// Băm mật khẩu đầu vào (dùng hash C++ chuẩn), trả về số nguyên size_t
size_t hashPassword(const string& pwd) {
    return hash<string>{}(pwd);
}

// Chuyển thời gian kiểu time_t thành chuỗi yyyy-mm-dd hh:mm:ss
string nowToString(time_t t) {
    struct tm lt {};
#ifdef _WIN32
    localtime_s(&lt, &t);   // Chuẩn Windows
#else
    localtime_r(&t, &lt);   // Chuẩn Linux
#endif
    char buf[64];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &lt); // Định dạng xuất chuỗi ngày giờ
    return string(buf);
}

// Nhập mật khẩu dạng ẩn: nhập ký tự nào thì hiển thị * lên màn hình thay vì chữ thật
// Kết thúc khi nhấn Enter; hỗ trợ xóa bằng Backspace
string inputHiddenPassword() {
    string password;
    char ch;
    while (true) {
        ch = _getch(); // Lấy ký tự nhập không hiện lên màn hình
        if (ch == '\r' || ch == '\n') { // Nếu nhấn Enter thì kết thúc nhập
            cout << endl;
            break;
        }
        if (ch == 8 || ch == 127) { // Xử lý xóa ký tự (Backspace hoặc Delete)
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b"; // Xóa ký tự * trên màn hình
            }
        }
        else {
            password.push_back(ch); // Lưu ký tự vào chuỗi mật khẩu
            cout << '*';            // Hiển thị * lên màn hình
        }
    }
    return password;
}

// Xóa toàn bộ màn hình console (tùy hệ điều hành)
// Windows dùng "cls", Linux/Mac dùng "clear"
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
