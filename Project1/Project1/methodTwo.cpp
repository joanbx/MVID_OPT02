#include "methodTwo.hpp"
#include "hexAid.hpp"
#include <iostream>

int getsizeBin(int size) {
	int _size = 1;
	if (size <= 4) _size = 2;
	else if (size <= 8) _size = 3;
	else if (size <= 16) _size = 4;
	//else if (size <= 32) _size = 5;

	return _size;
}

std::vector<char>  methodTwo::getOriginal(const std::vector<char>& reduced) {

	//El vector tiene una cadena tal que así
	// [0] -> n: Número de distintos caracteres
	// [1-n+1] -> Distintos caracteres usados
	// [n+2,final] -> Cadena a convertir

	std::vector<char> vout;

	int num = hexAid::hex_to_int(reduced[0]); //Número de distintos caracteres
	std::vector<char> data(reduced.begin() + num + 1, reduced.end()); //Se trata de la cadena comprimida
	std::vector<char> buffer(reduced.begin() + 1, reduced.begin() + num + 1); //Se trata de todos los diferentes tipos de char

	int _size = getsizeBin(buffer.size());
	
	std::vector<bool> vbin(7, 0);
	std::vector<bool> vbinTotal;

	//Data en formato binario

	for (int h = 0; h < data.size(); h++) {
		for (int b = 0; b < 7; b++) {
			vbin[b] = (data[h] >> b) & 1;
		}

		vbinTotal.insert(vbinTotal.end(), vbin.begin(), vbin.end());
	}

	vbin.clear();

	//Por toda la cadena en binario, recogemos de _size en _size y vemos a qué char pertenece

	std::vector<bool> vbinb(_size, 0);
	uint8_t count = 0;
	for (int i = 0; i < vbinTotal.size(); ++i) {
		vbinb[count] = vbinTotal[i];
		count++;
		if (count == _size) {
			count = 0;
			size_t t = hexAid::bool2size_t(vbinb);
			vout.push_back(buffer[(int)hexAid::bool2size_t(vbinb)]);
		}
	}

	//Clear vectors
	data.clear();
	vbinb.clear();
	buffer.clear();
	vbinTotal.clear();

	return vout;
}


std::vector<char> methodTwo::reduceString(const std::vector<char>& originalData, const std::vector<char>& dataBuffer) {

	std::vector<char> dataReduced;

	std::vector<bool> vb;

	//Con getsizeBin sabemos cuantos binarios necesitamos teniendo en cuenta cuantos char distintos tenemos. Y luego unimos toda la secuencia binaria
	//Si char distintos <= 2 -> size = 2 -   00
	//Si char distintos [3,4] -> size = 3 -  000
	//Si char distintos [5,8] -> size = 4 -  0000
	//Si char distintos [9,16] -> size = 5 - 00000
	//Sabemos que un char es un byte, y ocupa 1byte u ocho bits, así que siempre ahorraremos mínimo 3 bits por cada char


	for (int h = 0; h < originalData.size(); h++) {

		for (int i = 0; i < dataBuffer.size(); i++) {
			if (originalData[h] == dataBuffer[i]) {
				int k = i;
				int _size = getsizeBin(dataBuffer.size());
				std::vector<bool> vb2(_size, 0);

				for (int p = 0; p < _size; p++) {
					vb2[p] = k & 1;
					k >>= 1;
				}
				vb.insert(vb.end(), vb2.begin(), vb2.end());
			}
		}

	}


	std::vector<char> reduced = hexAid::bools_to_ascii(vb);

	dataReduced.insert(std::end(dataReduced), std::begin(reduced), std::end(reduced));

	reduced.clear();
	vb.clear();

	return dataReduced;

}