#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "geo.h"
#include "lista.h"
#include "fila.h"
#include "reta.h"
#include "circ.h"
#include "retang.h"
#include "texto.h"
#include "coords.h"

void leGeo(char* BED, char* BSD, char* geo, Lista retangulos, Lista circulos, Lista textos, Lista retas, Lista selecionadas, Fila corrente, Lista coords){
    if( BED == NULL || BSD == NULL || geo == NULL || retangulos == NULL || circulos == NULL || textos == NULL || retas == NULL || selecionadas == NULL || corrente == NULL || coords == NULL){
        return;
    }

    int tamBED = strlen(BED);
    int tamGeo = strlen(geo);

    int temBarra = BED[tamBED-1] == '/';
    
    char* geoCaminho = malloc(tamBED + tamGeo + !temBarra + 20);

    if(geoCaminho == NULL){
        return;
    }

    if(temBarra){
        sprintf(geoCaminho, "%s%s", BED, geo);
    } else{
        sprintf(geoCaminho, "%s/%s", BED, geo);
    }

    FILE* geoFile = fopen(geoCaminho, "r");

    free(geoCaminho);

    char* geoNome = strtok(geo, ".");
    int tamBSD = strlen(BSD);
    temBarra = BSD[tamBSD-1] == '/';
    char* svgNome = malloc(tamBSD + strlen(geoNome) + 5 + !temBarra);

    if(temBarra){
        sprintf(svgNome, "%s%s.svg", BSD, geoNome);
    } else{
        sprintf(svgNome, "%s/%s.svg", BSD, geoNome);
    }

    FILE* svg = fopen(svgNome,"w");
    printf("%s", svgNome);
    fprintf(svg, "<svg>\n");

    char aux[999];    

    while(1){
        fgets(aux, 999, geoFile);
        if(feof(geoFile)){
            break;
        }

        if(aux[strlen(aux)-1] == '\n'){
            aux[strlen(aux)-1] = '\0';
        }
        
        
        char* arg = strtok(aux, " ");

        char* id;
        char* x;
        char* y;
        char* x1;
        char* y1;
        char* x2;
        char* y2;
        char* cor;
        char* corB;
        char* corP;
        char* r;
        char* texto;
        char* a;
        char* l;
        char* ancora;
        char tipo[999];
        double x1dbl;
        double x2dbl;
        double y1dbl;
        double y2dbl;
        Coords nCoords;

        switch(arg[0]){
            case 'l':
                id = strtok(NULL, " ");
                x1 = strtok(NULL, " ");
                y1 = strtok(NULL, " ");
                x2 = strtok(NULL, " ");
                y2 = strtok(NULL, " ");
                cor = strtok(NULL, " ");
                Reta nReta = criaReta(x1, x2, y1, y2, cor, id);
                retaSvg(svg, nReta);
                insLista(retas, nReta);

                sscanf(x1, "%lf", &x1dbl);
                sscanf(x2, "%lf", &x2dbl);
                sscanf(y1, "%lf", &y1dbl);
                sscanf(y2, "%lf", &y2dbl);
                strcpy(tipo, "l");
                if(x1dbl < x2dbl){
                    nCoords = criaCoords(id, x1, y1, tipo);
                    insLista(coords, nCoords);}
                if(x2dbl < x1dbl){
                    nCoords = criaCoords(id, x2, y2, tipo);
                    insLista(coords, nCoords);
                }
                if(x1dbl == x2dbl && y1dbl < y2dbl){
                    nCoords = criaCoords(id, x1, y1, tipo);
                    insLista(coords, nCoords);
                }
                if(x1dbl == x2dbl && y2dbl < y1dbl){
                    nCoords = criaCoords(id, x2, y2, tipo);
                insLista(coords, nCoords);
                }
                break;

            case 'r':
                strcpy(tipo, "r");
                id = strtok(NULL, " ");
                x = strtok(NULL, " ");
                y = strtok(NULL, " ");
                l = strtok(NULL, " ");
                a = strtok(NULL, " ");
                corB = strtok(NULL, " ");
                corP = strtok(NULL, " ");
                Retang nRetang = criaRetang(x, y, a, l, corB, corP, id);
                nCoords = criaCoords(id, x, y, tipo);
                insLista(coords, nCoords);
                retangSvg(svg, nRetang);
                insLista(retangulos, nRetang);     
                break;

            case 'c':
                strcpy(tipo, "c");
                id = strtok(NULL, " ");
                x = strtok(NULL, " ");
                y = strtok(NULL, " ");
                r = strtok(NULL, " ");
                corB = strtok(NULL, " ");
                corP = strtok(NULL, " ");
                Circ nCirc = criaCirc(x, y, r, corB, corP, id);
                nCoords = criaCoords(id, x, y, tipo);
                insLista(coords, nCoords);
                circSvg(svg, nCirc);
                insLista(circulos, nCirc);
                break;

            case 't':
                strcpy(tipo, "t");
                id = strtok(NULL, " ");
                x = strtok(NULL, " ");
                y = strtok(NULL, " ");
                corB = strtok(NULL, " ");
                corP = strtok(NULL, " ");
                ancora = strtok(NULL, " ");
                texto = corP + strlen(corP) + 1;

                switch(ancora[0]){
                    case 'i':
                        strcpy(ancora, "start");
                        break;
                    case 'm':
                        strcpy(ancora, "middle");
                        break;
                    case 'f':
                        strcpy(ancora, "end");
                        break;
                    default:
                        break;
                }
                
                Texto nTexto = criaTexto(x, y, texto, corB, corP, ancora, id);
                nCoords = criaCoords(id, x, y, tipo);
                insLista(coords, nCoords);
                textoSvg(svg, nTexto);
                insLista(textos, nTexto);
                break;
            default:
                break;
        }
    }
    fprintf(svg, "</svg>\n");



}
