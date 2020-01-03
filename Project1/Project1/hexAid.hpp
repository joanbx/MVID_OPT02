#pragma once
#include <vector>

class hexAid {
public:
	static int hex_to_int(char c);
	static char int_to_hex(int n);
	static char high_nibble(unsigned int v);
	static char low_nibble(unsigned int v);
	static int hex_to_ascii(char c, char d);
	static inline size_t bool2size_t(std::vector<bool>& in);
	static std::vector<char> bools_to_ascii(std::vector<bool>& in);
};