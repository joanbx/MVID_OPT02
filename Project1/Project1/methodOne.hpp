#pragma once
#include <vector>

class methodOne {
public:
	static std::vector<char> getOriginal(std::vector<char>& reduced);
	static std::vector<char> reduceString(std::vector<char>& originalData, std::vector<char>& dataBuffer);

};