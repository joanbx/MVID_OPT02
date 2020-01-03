#pragma once
#include <vector>
class methodTwo {
public:
	static std::vector<char> getOriginal(const std::vector<char>& reduced);
	static std::vector<char> reduceString(const std::vector<char>& originalData, const std::vector<char>& dataBuffer);

};