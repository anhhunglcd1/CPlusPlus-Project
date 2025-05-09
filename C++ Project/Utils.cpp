#include "login_system.h"
#include <random>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>   // for system()
using namespace std;

string genRandomPassword(int length) {
    static const char chars[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789";
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, static_cast<int>(sizeof(chars) - 2));
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
    char buf[64] = { 0 };
    if (strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &lt) > 0)
        return string(buf);
    return "<invalid_time>";
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
