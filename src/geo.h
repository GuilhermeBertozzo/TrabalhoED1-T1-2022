#ifndef MODULO_GEO
#define MODULO_GEO

#include "lista.h"
#include "fila.h"

// Formata o path e le o arquivo .geo, salvado e alterando as formas em listas diferentes.
void leGeo(char* BED, char* BSD, char* geo, Lista retangulos, Lista circulos, Lista textos, Lista retas, Lista selecionadas, Fila corrente, Lista coords); 

#endif