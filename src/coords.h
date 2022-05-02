#ifndef MODULO_COORDS
#define MODULO_COORDS
#include <stdio.h>

typedef struct coords* Coords;

// Cria uma struct do tipo Coords que armazena as coordenadas, o tipo e o id da forma.
Coords criaCoords(char* id, char* x, char* y, char* tipo); 

//Retorna o elemento x do elemento coords.
char* getCoordX(Coords coords);

//Retorna o elemento y do elemento coords.
char* getCoordY(Coords coords);

//Retorna o elemento id do elemento coords.
char* getCoordID(Coords coords);

//Retorna o elemento tipo do elemento coords.
char* getCoordTipo(Coords coords);
//Desfar a struct coords, liberando toda a memoria alocada.
void desfazCoord(Coords coords);

#endif