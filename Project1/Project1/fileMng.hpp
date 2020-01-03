#pragma once
#include <string>
#include <vector>

class fileMng {
public:
	static void readFile(std::string const& fileName, std::vector<char>& result);
	static void writeFile(const std::vector<char>& myVector, std::string const& fileName);
	static bool exists_file(const std::string& name);
};