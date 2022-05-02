#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include "qry.h"
#include "geo.h"
#include "fila.h"
#include "lista.h"
#include "circ.h"
#include "retang.h" 
#include "reta.h"
#include "texto.h"

int main(int argc, char* argv[]){
    char* BED = NULL;
    char* BSD = NULL;
    char* geo = NULL;
    char* qry = NULL;

    char leitura;
    while((leitura = getopt(argc, argv, "e:f:o:q:"))!= -1){
        switch(leitura){
            case 'e':
                BED = malloc(strlen(optarg)+1);
                strcpy(BED, optarg);
                break;
            case 'f':
                geo = malloc(strlen(optarg)+1);
                strcpy(geo, optarg);
                break;
            case 'o':
                BSD = malloc(strlen(optarg)+1);
                strcpy(BSD, optarg);
                break;
            case 'q':
                qry = malloc(strlen(optarg)+1);
                strcpy(qry, optarg);
                break;
            default:
                break;
        } 
    }

    if(geo == NULL){
        printf("O argumento 'f' e obrigatorio. ");
        return -1;
    }

    if(BSD == NULL){
        printf("O argumento 'o' e obrigatorio. ");
        return -1;
    }

    Lista retangulos = criaLista();
    Lista circulos = criaLista();
    Lista textos = criaLista();
    Lista retas = criaLista();
    Lista coords = criaLista();
    Lista selecionadas = criaLista();
    Fila corrente = criaFila();

    leGeo(BED, BSD, geo, retangulos, circulos, textos, retas, selecionadas, corrente, coords);
    leQry(BED, BSD, qry, geo, retangulos, circulos, textos, retas, selecionadas, corrente, coords);

}