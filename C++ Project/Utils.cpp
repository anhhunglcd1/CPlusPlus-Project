#include "login_system.h"
#include <random>
#include <sstream>
#include <iomanip>

string genRamdomPassword(int length)
{
	static const char chars[]=
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

string genOTP(int digits)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0, pow(10, digits) - 1);
	ostringstream ss;
	ss << setw(digits) << setfill('0') << dis(gen);
	return ss.str();
}

size_t hashPassword(const string& pwd)
{
	return hash<string>{}(pwd);
}

string nowToString(time_t t) {
	struct tm lt;
	localtime_s(&lt, &t);
	char buf[64] = { 0 };
	if (strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &lt) > 0) {
		return string(buf);
	}
	else {
		return string("<invalid_time>");
	}
}