#pragma once
#include <string>
#include <sstream>
using std::string;
using std::stringstream;

string toBinary(int num) {
	if (num < 0 || num > 512) return "";
	stringstream builder;
	for (int i = 8; i >= 0; i--) {
		int digit = (num >> i) & 1;
		builder << digit;
	}
	return builder.str();	
}
