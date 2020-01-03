# README
El siguiente programa está dividido en dos partes:
* Leer fichero binario de entrada y comprimirlo en fichero salida
* Leer fichero comprimido de salida e imprimir la cadena original

## Programa
El programa principal es Main.cpp
Luego hemos creado las siguientes clases:
* fileMng (funciones para escribir o leer de un fichero)
* hexAid (funciones de ayuda para manipulación de hexadecimales/binarios/decimales)
* methodOne (funciones para compresión de fichero y recuperación cadena original por método 1)
* methodTwo (funciones para compresión de fichero y recuperación cadena original por método 2)

## Método de compresión
Hemos optado por dos métodos distintos de compresión.
Para cambiar de un método a otro:
>const compressType _TYPE = compressType::Two; //o compressType::One

En ambos casos, la cadena sigue la siguiente estructura:

>[0] -> n: Número de distintos caracteres
[1,n+1] -> Distintos caracteres usados
[n+2,final] -> Cadena comprimida

### Método 1
Convertiremos cada dos carácteres en un char ascii
Por ejemplo la cadena ABBACA tiene tres carácteres distintos (0->A,1->B,2->C), con lo que convertiremos AB en 0x01 que en ascii es el carácter "SOH", luego viene BA que es 0x10 "DLE" en ascii, y así sucesivamente...
De esta forma reducimos 2bytes en 1

### Método 2
Sabemos que cada char necesita 1 byte (8bits), pero si hay menos 16 carácteres distintos, solamente necesitaríamos máximo 5bits, cómo se muestra a continuación:
>Si char distintos <= 4 -> size = 2 ->   00
Si char distintos [5,8] -> size = 3 ->  000
Si char distintos [9,16] -> size = 4 ->  0000

Lo que haremos será juntar de size en size los bits, y luego obtendremos un array/vector de nuevos chars (cada 8 bits obtenemos un char, aunque en realidad son 7, por que el código ascii va de 0 a 127).  

Por ejemplo la cadena ABBACA tiene tres carácteres distintos (0->A,1->B,2->C).
size = 2
-A--B--B--A--C--A-
00 01 01 00 10 00 -> Dividimos en cadenas de siete bits
00 01 01 0 -> char(10)
0 10 00 -> char(8)
Por tanto hemos comprimido una cadena de 6 char en una de 2.

### Resumen
Generalmente el segundo método será mas eficiente para cadenas largas y cuánto menos carácteres distintos, mas eficiente será. El método primero es mas constante en la compresión, ya que se divide siempre entre dos (además de los carácteres distintos que tenemos al principio de la cadena comprimida)

