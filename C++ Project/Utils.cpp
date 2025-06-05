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

// =======================
// Sinh mật khẩu ngẫu nhiên
// =======================
// Tạo một chuỗi gồm chữ cái hoa, thường, và số, có độ dài tùy ý (length)
// Đảm bảo mỗi lần sinh đều khác nhau nhờ random_device và mt19937
string genRandomPassword(int length) {
    static const char chars[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789"; // Dãy ký tự hợp lệ để sinh mật khẩu
    random_device rd;             // Lấy seed ngẫu nhiên từ phần cứng
    mt19937 gen(rd());            // Bộ sinh số ngẫu nhiên chất lượng cao
    uniform_int_distribution<> dis(0, sizeof(chars) - 2); // Random chỉ số trong dãy ký tự
    string s;
    for (int i = 0; i < length; ++i)
        s += chars[dis(gen)];     // Lấy random một ký tự và ghép vào chuỗi kết quả
    return s;                     // Trả về chuỗi mật khẩu đã tạo
}

// ==================
// Sinh mã OTP ngẫu nhiên
// ==================
// Sinh số nguyên ngẫu nhiên có đúng số chữ số (digits), đủ 0 đầu nếu cần (ví dụ "004521")
// OTP chỉ chứa ký tự số, không lẫn chữ cái
string genOTP(int digits) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, static_cast<int>(pow(10, digits)) - 1);
    ostringstream ss;
    ss << setw(digits) << setfill('0') << dis(gen); // In đủ chữ số, nếu thiếu sẽ tự chèn '0'
    return ss.str();
}

// =========================
// Băm mật khẩu (hash password)
// =========================
// Nhận vào chuỗi mật khẩu, trả về số nguyên size_t (giá trị băm)
// Không bao giờ lưu mật khẩu gốc vào file - tăng bảo mật hệ thống
size_t hashPassword(const string& pwd) {
    return hash<string>{}(pwd);
}

// =======================================
// Chuyển time_t thành chuỗi "yyyy-mm-dd hh:mm:ss"
// =======================================
// Dùng để in lịch sử giao dịch, thời điểm xác nhận OTP, v.v.
string nowToString(time_t t) {
    struct tm lt {};
#ifdef _WIN32
    localtime_s(&lt, &t);   // Lấy struct tm trên Windows (an toàn)
#else
    localtime_r(&t, &lt);   // Lấy struct tm trên Linux/Mac (an toàn)
#endif
    char buf[64];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &lt); // Chuyển struct tm thành chuỗi chuẩn
    return string(buf);      // Trả về chuỗi ngày-giờ định dạng chuẩn
}

// ==============================
// Nhập mật khẩu dạng ẩn (hiện dấu *)
// ==============================
// Khi nhập mật khẩu, chỉ hiện dấu * thay vì ký tự thật, tránh lộ mật khẩu
// Có hỗ trợ xóa từng ký tự bằng phím Backspace/Delete
string inputHiddenPassword() {
    string password;
    char ch;
    while (true) {
        ch = _getch(); // Đọc 1 ký tự, không in ra màn hình (chỉ hỗ trợ trên Windows)
        if (ch == '\r' || ch == '\n') { // Enter: kết thúc nhập
            cout << endl;
            break;
        }
        if (ch == 8 || ch == 127) { // Backspace hoặc Delete: xóa ký tự cuối
            if (!password.empty()) {
                password.pop_back();   // Xóa trong bộ nhớ
                cout << "\b \b";       // Xóa cả ký tự * trên màn hình
            }
        }
        else {
            password.push_back(ch); // Lưu ký tự vừa nhập vào chuỗi
            cout << '*';            // Hiển thị * thay cho ký tự thật
        }
    }
    return password; // Trả về chuỗi đã nhập
}

// ==============================
// Xóa màn hình console
// ==============================
// Gọi lệnh hệ điều hành: "cls" (Windows) hoặc "clear" (Linux/Mac)
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
