#include "hexAid.hpp";
#include <sstream>
#include <cassert>

//Char (HEX) to int
int hexAid::hex_to_int(char c) {
	int first = c / 16 - 3;
	int second = c % 16;
	int result = first * 10 + second;
	if (result > 9) result--;
	return result;
}

//int to single hex
char hexAid::int_to_hex(int n) {
	char hex[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	return hex[n];
}
//return high nibble (Char Hex) from int
char hexAid::high_nibble(unsigned int v)
{
	std::ostringstream stm;
	stm << std::hex << std::uppercase << v;
	return stm.str().front();
}
//return Low nibble (Char Hex) from int
char hexAid::low_nibble(unsigned int v)
{
	std::ostringstream stm;
	stm << std::hex << std::uppercase << v;
	return stm.str().back();
}
//Hex to ascii
int hexAid::hex_to_ascii(char c, char d) {
	int high = hex_to_int(c) * 16;
	int low = hex_to_int(d);
	return high + low;
}


//Bool to int
inline size_t hexAid::bool2size_t(std::vector<bool>& in) {
	assert(sizeof(size_t) * CHAR_BIT >= in.size());
	size_t out(0);

	for (size_t vecPos = 0; vecPos < in.size(); vecPos++) {
		if (in[vecPos]) {
			out += 1 << vecPos;
		}
	}

	return out;
}
//from an array of bools return an array of ascii chars
std::vector<char> hexAid::bools_to_ascii(std::vector<bool>& in) {
	std::vector<char> Bascii;
	for (int i = 0; i < in.size(); i += 7) {
		int _range = 7;
		if (i + _range > in.size() - 1) _range = in.size() - 1 - i;

		std::vector<bool> range(in.begin() + i, in.begin() + i + _range);


		size_t I = (char)bool2size_t(range);

		range.clear();
		Bascii.push_back(I);
	}

	return Bascii;
}
