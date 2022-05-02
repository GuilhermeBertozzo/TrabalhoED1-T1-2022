#ifndef MODULO_QRY
#define MODULO_QRY

#include "lista.h"
#include "fila.h"

//Insere no polígono corrente as coordenadas da âncora da figura identificada por i. No caso de linhas, insere a extremidade de menor x (se empate, de menor y)
void inp(Lista coords, Fila corrente);

//Remove a coordenada mais antiga inserida no poligono corrente.
void rmp(FILE* txtFile, Fila corrente);

//Remove todas as coordenadas do políigono corrente.
void clp(Fila corrente);

//Seleciona as figuras inteiramente dentro da região especificada pelos parâmetros. (Desconsidera seleções anteriores)
void sel(FILE* txtFile, Lista coords, Lista selecionadas, Lista retangulos, Lista circulos, Lista retas, Lista textos);

//Semelhante à operação sel, porém, acrescenta as figuras selecionadas àquelas anteriormente selecionadas.
void selM(FILE* txtFile, Lista coords, Lista selecionadas, Lista retangulos, Lista circulos, Lista retas, Lista textos);

//Remove das listas todas as figuras selecionadas.
void dels(Lista coords, Lista selecionadas, Lista retangulos, Lista circulos, Lista retas, Lista textos);

// Formata o path e le o arquivo .qry, salvado e alterando as formas em listas diferentes.
void leQry(char* BED, char* BSD, char* qry, char* geo, Lista retangulos, Lista circulos, Lista textos, Lista retas, Lista selecionadas, Fila corrente, Lista coords); 

#endif