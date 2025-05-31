#include "login_system.h"
#include <random>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <conio.h>
using namespace std;

string genRandomPassword(int length) {
    static const char chars[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789";
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, sizeof(chars) - 2);
    string s;
    for (int i = 0; i < length; ++i)
        s += chars[dis(gen)];
    return s;
}

string genOTP(int digits) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, static_cast<int>(pow(10, digits)) - 1);
    ostringstream ss;
    ss << setw(digits) << setfill('0') << dis(gen);
    return ss.str();
}

size_t hashPassword(const string& pwd) {
    return hash<string>{}(pwd);
}

string nowToString(time_t t) {
    struct tm lt {};
#ifdef _WIN32
    localtime_s(&lt, &t);
#else
    localtime_r(&t, &lt);
#endif
    char buf[64];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &lt);
    return string(buf);
}

string inputHiddenPassword() {
    string password;
    char ch;
    while (true) {
        ch = _getch();
        if (ch == '\r' || ch == '\n') {
            cout << endl;
            break;
        }
        if (ch == 8 || ch == 127) {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        }
        else {
            password.push_back(ch);
            cout << '*';
        }
    }
    return password;
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
