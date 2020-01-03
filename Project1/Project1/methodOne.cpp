#include "methodOne.hpp"
#include "hexAid.hpp"
#include <vector>

//Funcion de transformación de cadena reducida a original
std::vector<char> methodOne::getOriginal(std::vector<char>& reduced) {

	//El vector tiene una cadena tal que así
	// [0] -> n: Número de distintos caracteres
	// [1-n+1] -> Distintos caracteres usados
	// [n+2,final] -> Cadena a convertir


	int count = hexAid::hex_to_int(reduced[0]); //Número de distintos caracteres

	std::vector<char> dataOutput;



	for (int k = count + 1; k < reduced.size(); k++) {

		if ((k == reduced.size() - 1) && (reduced.size() - count - 1) % 2 != 0) { //Si es el último elemento y la cadena es impar, cogemos directamente el valor
			dataOutput.push_back(reduced[k]);
		}
		else { //Un Ascii tiene dos Hex, que seran los que utilizaremos para reorganizar el original, por ejemplo A=0x41 que corresponderá al valor guardado en el índice 4 y 1.
			int high = 0;
			int low = 0;

			if (int(reduced[k]) > 16) {
				high = hexAid::hex_to_int(hexAid::high_nibble(int(reduced[k])));
			}
			low = hexAid::hex_to_int(hexAid::low_nibble(int(reduced[k])));
			dataOutput.push_back(reduced[high + 1]);
			dataOutput.push_back(reduced[low + 1]);
		}


	}

	return dataOutput;

}

//Función de transformación de original a cadena reducida
std::vector<char> methodOne::reduceString(std::vector<char>& originalData, std::vector<char>& dataBuffer) {
	

	std::vector<char> dataReduced;

	//Convertiremos cada dos carácteres en un char ascii
	//Por ejemplo la cadena ABBACA tiene tres carácteres distintos (0->A,1->B,2->C), con lo que convertiremos AB en 0x01 que en ascii es el carácter "SOH", luego viene BA que es 0x10 "DLE" en ascii, y así sucesivamente...
	//De esta forma reducimos 2bytes en 1
	char pos1 = ' ';
	char pos2 = ' ';
	char asciiChar = ' ';

	for (int h = 0; h < originalData.size(); h += 2) {
		if (h + 1 < originalData.size()) {

			for (int i = 0; i < dataBuffer.size(); i++) {
				if (originalData[h] == dataBuffer[i]) pos1 = hexAid::int_to_hex(i);
				if (originalData[h + 1] == dataBuffer[i]) pos2 = hexAid::int_to_hex(i);
			}
			//Cada ascii tiene dos hex, que será el que queremos para reducir la cadena
			asciiChar = hexAid::hex_to_ascii(pos1, pos2);
		}
		else { //Si se tenemos una cadena impar, el último char se queda igual
			asciiChar = originalData[h];
		}

		dataReduced.push_back(asciiChar); //añadimos el caracter al vector
	}

	//dataReduced.push_back(int_to_hex(dataBuffer.size())); //El primero es el número de characteres distintos (<=16)

	return dataReduced;

}