#include "fileMng.hpp"
#include "methodOne.hpp"
#include "methodTwo.hpp"
#include "hexAid.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

//ENUM
enum class compressType {
	One,
	Two
};


//GLOBAL VARS
const std::string INPUTFILENAME = "../input.dat";
const std::string OUTPUTFILENAME = "../output.dat";
const compressType _TYPE = compressType::Two;

//#Funciones
std::vector<char> compressData(vector<char>& originalData, compressType cType) {

	vector<char> dataBuffer;
	bool encontrado = false;

	//Queremos saber cuantos carácteres distintos hay
	for (int i = 0; i < originalData.size(); ++i)
	{
		encontrado = false;
		for (int j = 0; j < dataBuffer.size(); ++j)
		{
			if (dataBuffer[j] == originalData[i])  encontrado = true;
		}
		if (encontrado == false) {
			dataBuffer.push_back(originalData[i]);
		}
	}
	vector<char> dataReduced;

	// Queremos hacer un vector tal que:
	// [0] -> n: Número de distintos caracteres <=16
	// [1,n+1] -> Distintos caracteres usados
	// [n+2,final] -> Cadena a convertir

	dataReduced.push_back(hexAid::int_to_hex(dataBuffer.size())); //El primero es el número de characteres distintos (<=16)
	for (int k = 0; k < dataBuffer.size(); ++k)
	{
		dataReduced.push_back(dataBuffer[k]); //Luego vienen todos los caracteres distintos
	}

	vector<char> getData;

	if (cType == compressType::One) {
		getData = methodOne::reduceString(originalData, dataBuffer);
	}
	else if (cType == compressType::Two) {
		getData = methodTwo::reduceString(originalData, dataBuffer);
	}

	dataReduced.insert(dataReduced.end(), getData.begin(), getData.end());

	dataBuffer.clear();
	getData.clear();

	return dataReduced;
}

vector<char> getOriginalData(vector<char>& reduced, compressType cType) {

	//El vector tiene una cadena tal que así
	// [0] -> n: Número de distintos caracteres
	// [1,n+1] -> Distintos caracteres usados
	// [n+2,final] -> Cadena a convertir

	vector<char> original;
	
	if (cType == compressType::One) {	
		original = methodOne::getOriginal(reduced);
	}
	else if (cType == compressType::Two) {
		original = methodTwo::getOriginal(reduced);
	}
	


	return original;


}

//#Funcón principal
int main() {

	char type = ' ';
	
	string inputData;
	vector<char> vInputData;

	if (!fileMng::exists_file(INPUTFILENAME)) { //Fichero no existe -> Creamos data
		cout << "Input file does not exist. Creating new one with custom values \n"  << std::endl;
		inputData = "RYKARRKAAGCWATYWKMTCTWRAGSRMGCTKGTKCACMYACYTTMG";
		copy(inputData.begin(), inputData.end(), std::back_inserter(vInputData));
		fileMng::writeFile(vInputData, INPUTFILENAME);
	}
	else { //Fichero existe -> Leemos
		fileMng::readFile(INPUTFILENAME, vInputData);
		copy(vInputData.begin(), vInputData.end(), back_inserter(inputData));
	}

	if (vInputData.size() > 0) { //Fichero tiene datos
		cout << "Input file contains following string: \n" << inputData << "\n------------------\n\n" << endl;
		
		do
		{
			cout << "Options \n 1.- Compress input file and write it in output \n 2.- Convert output file into the original" << endl;
			cin >> type;
		} while (!cin.fail() && type != '1' && type != '2');

		if (type == '1') {
			//Compress Input
			cout << "Compress Input " << endl;

			vector<char> reduced = compressData(vInputData, _TYPE);

			//Write to file
			fileMng::writeFile(reduced, OUTPUTFILENAME);
			reduced.clear();
		}


		else if (type == '2') {
			//Read Output
			
			cout << "Read Output " << endl;
			
			//vector<char> vDataOutput;
			//fileMng::readFile(OUTPUTFILENAME, vDataOutput); // Leemos el archivo en un vector (no usamos esta funcion, queremos hacerlo en memoria ahora)

			
			char* memblock; //Bloque de memoria que usaremos para guardar el fichero
			std::streampos size;
			std::ifstream file(OUTPUTFILENAME, std::ios::in | std::ios::binary | std::ios::ate);
			if (file.is_open())
			{
				size = file.tellg();
				memblock = new char[size];
				file.seekg(0, std::ios::beg);
				file.read(memblock, size);
				file.close();

				vector<char> vDataOutput(memblock, memblock + size); //Podemos acceder a memblock que está en la MEMORIA y pasarlo a un vector (ya que estamos usandolos en todo nuestro programa)
				vector<char> original = getOriginalData(vDataOutput, _TYPE); //Datos originales

				//Resultado:
				for (int i = 0; i < original.size(); ++i) {
					cout << original[i];
				}

				//Clear//Delete
				original.clear();
				vDataOutput.clear();
				delete[] memblock;
			}
			else {
				cout << "Output file does not exist " << endl;
			}

			
		}
	}
	else {
		cout << "Input file does not contain any data, nothing to do..." << endl;
	}
	
	
	vInputData.clear();
	
	
	
	return 0;
}
