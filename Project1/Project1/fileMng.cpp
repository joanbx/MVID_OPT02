#include "fileMng.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>

//Leer Fichero
void fileMng::readFile(std::string const& fileName, std::vector<char>& result)
{

	std::ifstream in(fileName, std::ios::in | std::ios::binary);
	in >> std::noskipws;
	copy(std::istream_iterator<char>(in),
		std::istream_iterator<char>(),
		back_inserter(result));
	in.close();

}

//Guardar Ficher
void fileMng::writeFile(const std::vector<char>& myVector, std::string const& fileName)
{
	std::ofstream fout(fileName, std::ios::out | std::ios_base::binary);
	size_t size = myVector.size();
	fout.write(reinterpret_cast<const char*>(&myVector[0]), myVector.size() * sizeof(char));
	fout.close();
}
//Fichero existe
bool fileMng::exists_file(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}