#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "qry.h"
#include "fila.h"
#include "lista.h"
#include "reta.h"
#include "circ.h"
#include "retang.h"
#include "texto.h"
#include "coords.h"


int idGen = 99999;

void inp(Lista coords, Fila corrente){
    char* id = strtok(NULL, " "); 
    char* x;
    char* y;
    char* tipo;  

    ListaPosic posic = primeiraPosicLista(coords);
    while(posic){
        Coords coordsCmp = getLista(coords, posic);
        if(strcmp(id, getCoordID(coordsCmp)) == 0){
            Coords Ncoord = criaCoords(id = getCoordID(coordsCmp), x = getCoordX(coordsCmp), y = getCoordY(coordsCmp), tipo = getCoordTipo(coordsCmp));
            insFila(corrente, Ncoord);
            return;
        }
        posic = prxPosicLista(coords, posic);
    }
}

void rmp(FILE* txtFile, Fila corrente){
    FilaPosic delPosic = primeiraPosicFila(corrente);
    Coords delCoords = getFila(corrente, delPosic);
    fprintf(txtFile, "Coordenadas sendo deletadas: x %s y %s\n", getCoordX(delCoords), getCoordY(delCoords));
    removeFila(corrente);
    return;
}

void clp(Fila corrente){
    while(tamFila(corrente)){
        removeFila(corrente);
    }
    return;
}

void sel(FILE* txtFile, Lista coords, Lista selecionadas, Lista retangulos, Lista circulos, Lista retas, Lista textos){
    limpaLista(selecionadas);

    char* coordIdL;
    char* coordIdR;
    char* coordIdC;
    char* coordIdT;
    char* lId;
    char* selX = strtok(NULL, " ");
    char* selY = strtok(NULL, " "); 
    char* selL = strtok(NULL, " "); 
    char* selA = strtok(NULL, " ");
    char corB[999];
    char corP[999];
    char tipo[999]; 
    char id[999];
    char r[999];  
    char* rId;
    char* cId;
    char* tId;
    char* lX1;
    char* lX2;
    char* lY1;
    char* lY2;
    char* rX;
    char* rY;
    char* rL;
    char* rA; 
    char* cX;
    char* cY;
    char* cR;
    char* tX;
    char* tY;
    char* idReta;
    char* idRetang;
    char* idCirc;
    char* idTexto;

    int overlap;

    ListaPosic posicL;
    ListaPosic posicR;
    ListaPosic posicC;
    ListaPosic posicT;
    ListaPosic selPosic;

    Reta lCmp;
    Retang rCmp;
    Circ cCmp;
    Texto tCmp;
    Coords nCoords;

    Circ nCirc;  

    double auxSelX;
    double auxSelY;
    double auxSelL;
    double auxSelA;
    double lAuxX1;
    double lAuxX2;
    double lAuxY1;
    double lAuxY2;
    double rAuxX;
    double rAuxY;
    double rAuxL;
    double rAuxA;
    double cAuxX;
    double cAuxY;
    double cAuxR;
    double tAuxX;
    double tAuxY;

    sprintf(id, "%d", idGen);
    sscanf(selX, "%lf", &auxSelX);
    sscanf(selY, "%lf", &auxSelY);
    sscanf(selL, "%lf", &auxSelL);
    sscanf(selA, "%lf", &auxSelA);

    strcpy(corB, "crimson");
    strcpy(corP, "crimson");
    strcpy(tipo, "r");
    strcpy(r, "1"); 

    Retang retSel = criaRetang(selX, selY, selA, selL, corB, corP, id);
    insLista(retangulos, retSel); 
    Coords nCoord = criaCoords(id, selX, selY, tipo);
    insLista(coords, nCoord);

    idGen--;

    ListaPosic posic = primeiraPosicLista(coords);
    while(posic){
        Coords coordCmp = getLista(coords, posic);
        char* tipoCmp = getCoordTipo(coordCmp);
        switch(tipoCmp[0]){
            case 'l':
                coordIdL = getCoordID(coordCmp);
                posicL = primeiraPosicLista(retas);
                while(posicL){
                    lCmp = getLista(retas, posicL);
                    lId = getIDReta(lCmp);
                    selPosic = primeiraPosicLista(selecionadas);
                    overlap = 1;
                    while(selPosic){
                        nCoords = getLista(selecionadas, selPosic);
                        idReta = getCoordID(nCoords);
                        if(strcmp(lId, idReta) == 0){
                            overlap = 0;
                            break;
                        }
                        selPosic = prxPosicLista(selecionadas, selPosic);
                    }
                    if(strcmp(lId, coordIdL) == 0 && overlap == 1){
                        lX1 = getX1Reta(lCmp);
                        lX2 = getX2Reta(lCmp);
                        lY1 = getY1Reta(lCmp);
                        lY2 = getY2Reta(lCmp);

                        sscanf(lX1, "%lf", &lAuxX1);
                        sscanf(lX2, "%lf", &lAuxX2);
                        sscanf(lY1, "%lf", &lAuxY1);
                        sscanf(lY2, "%lf", &lAuxY2);

                        if(lAuxX1 > auxSelX && lAuxX1 < (auxSelX + auxSelL) && lAuxX2 > auxSelX && lAuxX2 < (auxSelX + auxSelL) && lAuxY1 > auxSelY && lAuxY1 < (auxSelY + auxSelA) && lAuxY2 > auxSelY && lAuxY2 < (auxSelY + auxSelA)){
                            insLista(selecionadas, coordCmp);
                            strcpy(tipo, "c");
                            sprintf(id, "%d", idGen);
                            nCirc = criaCirc(lX1, lY1, r, corB, corP, id);
                            nCoord = criaCoords(id, lX1, lY1, tipo);
                            idGen--; 

                            insLista(circulos, nCirc);
                            insLista(coords, nCoord);
                            strcpy(tipo, "Linha");
                            fprintf(txtFile, "Id e tipo da figura selecionada: Id %s Tipo %s\n", getCoordID(nCoord), tipo);
                        } 
                    }
                    posicL = prxPosicLista(retas, posicL);
                }
                break;

            case 'r':
                coordIdR = getCoordID(coordCmp);
                posicR = primeiraPosicLista(retangulos);
                while(posicR){
                    rCmp = getLista(retangulos, posicR);
                    rId = getIDRetang(rCmp);
                    selPosic = primeiraPosicLista(selecionadas);
                    overlap = 1;
                    while(selPosic){
                        nCoords = getLista(selecionadas, selPosic);
                        idRetang = getCoordID(nCoords);
                        if(strcmp(rId, idRetang) == 0){
                            overlap = 0;
                            break;
                        }
                        selPosic = prxPosicLista(selecionadas, selPosic);
                    }
                    if(strcmp(rId, coordIdR) == 0 && overlap == 1){
                        rX = getXRetang(rCmp);
                        rY = getYRetang(rCmp);
                        rL = getLRetang(rCmp);
                        rA = getARetang(rCmp);

                        sscanf(rX, "%lf", &rAuxX);
                        sscanf(rY, "%lf", &rAuxY);
                        sscanf(rL, "%lf", &rAuxL);
                        sscanf(rA, "%lf", &rAuxA);

                        if(rAuxX > auxSelX && rAuxL < auxSelL && rAuxY > auxSelY && rAuxA < auxSelA){
                            insLista(selecionadas, coordCmp); 

                            
                            strcpy(tipo, "c");
                            sprintf(id, "%d", idGen);
                            nCirc = criaCirc(rX, rY, r, corB, corP, id);
                            nCoord = criaCoords(id, rX, rY, tipo);
                            idGen--; 

                            insLista(circulos, nCirc);
                            insLista(coords, nCoord);
                            strcpy(tipo, "Retangulo");
                            fprintf(txtFile, "Id e tipo da figura selecionada: Id %s Tipo %s\n", getCoordID(nCoord), tipo);

                        }
                    }
                    posicR = prxPosicLista(retangulos, posicR);      
                }
                break;

            case 'c':
                coordIdC = getCoordID(coordCmp);
                posicC = primeiraPosicLista(circulos);
                while(posicC){
                    cCmp = getLista(circulos, posicC);
                    cId = getIDCirc(cCmp);
                    selPosic = primeiraPosicLista(selecionadas);
                    int overlap = 1;
                    while(selPosic){
                        nCoords = getLista(selecionadas, selPosic);
                        idCirc = getCoordID(nCoords);
                        if(strcmp(cId, idCirc) == 0){
                            overlap = 0;
                            break;
                        }
                        selPosic = prxPosicLista(selecionadas, selPosic);
                    }
                    if(strcmp(cId, coordIdC) == 0 && overlap == 1){
                        cX = getXCirc(cCmp);
                        cY = getYCirc(cCmp);
                        cR = getRaioCirc(cCmp);

                        sscanf(cX, "%lf", &cAuxX);
                        sscanf(cY, "%lf", &cAuxY);
                        sscanf(cR, "%lf", &cAuxR);


                        if((cAuxX - cAuxR) > auxSelX && (cAuxX + cAuxR) < (auxSelX + auxSelL) && (cAuxY - cAuxR) > auxSelY && (cAuxY + cAuxR) < (auxSelY + auxSelA)){
                            insLista(selecionadas, coordCmp); 

                            
                            strcpy(tipo, "c");
                            sprintf(id, "%d", idGen);
                            nCirc = criaCirc(cX, cY, r, corB, corP, id);
                            nCoord = criaCoords(id, cX, cY, tipo);
                            idGen--; 

                            insLista(circulos, nCirc);
                            insLista(coords, nCoord);
                            
                            fprintf(txtFile, "Id e tipo da figura selecionada: Id %s Tipo %s\n", getCoordID(nCoord), tipo);

                        }
                    }
                    posicC = prxPosicLista(circulos, posicC);      
                }

                break;

            case 't':
                coordIdT = getCoordID(coordCmp);
                posicT = primeiraPosicLista(textos);
                while(posicT){
                    tCmp = getLista(textos, posicT);
                    tId = getIDTexto(tCmp); 
                    selPosic = primeiraPosicLista(selecionadas);
                    overlap = 1;
                    while(selPosic){
                        nCoords = getLista(selecionadas, selPosic);
                        idTexto = getCoordID(nCoords);
                        if(strcmp(tId, idTexto) == 0){
                            overlap = 0;
                            break;
                        }
                        selPosic = prxPosicLista(selecionadas, selPosic);
                    }
                    if(strcmp(tId, coordIdT) == 0 && overlap == 1){
                        tX = getXTexto(tCmp);
                        tY = getYTexto(tCmp);
                        
                        sscanf(tX, "%lf", &tAuxX);
                        sscanf(tY, "%lf", &tAuxY);

                        if(tAuxX > auxSelX && tAuxX < (auxSelX + auxSelL) && tAuxY > auxSelY && tAuxY < (auxSelY + auxSelA)){
                            insLista(selecionadas, coordCmp);

                            
                            strcpy(tipo, "c");
                            sprintf(id, "%d", idGen);
                            nCirc = criaCirc(tX, tY, r, corB, corP, id);
                            nCoord = criaCoords(id, tX, tY, tipo);
                            idGen--; 

                            insLista(circulos, nCirc);
                            insLista(coords, nCoord);
                            strcpy(tipo, "Texto");
                            fprintf(txtFile, "Id e tipo da figura selecionada: Id %s Tipo %s\n", getCoordID(nCoord), tipo);
                        }
                    }
                    posicT = prxPosicLista(textos, posicT);      
                }

                break;

            default:
                break;    
        }
        posic = prxPosicLista(coords, posic);
    }
}

void selM(FILE* txtFile, Lista coords, Lista selecionadas, Lista retangulos, Lista circulos, Lista retas, Lista textos){

    char* coordIdL;
    char* coordIdR;
    char* coordIdC;
    char* coordIdT;
    char* lId;
    char* selX = strtok(NULL, " ");
    char* selY = strtok(NULL, " "); 
    char* selL = strtok(NULL, " "); 
    char* selA = strtok(NULL, " ");
    char corB[999];
    char corP[999];
    char tipo[999]; 
    char id[999];
    char r[999]; 
    char* rId;
    char* cId;
    char* tId;
    char* lX1;
    char* lX2;
    char* lY1;
    char* lY2;
    char* rX;
    char* rY;
    char* rL;
    char* rA; 
    char* cX;
    char* cY;
    char* cR;
    char* tX;
    char* tY;
    char* idReta;
    char* idRetang;
    char* idCirc;
    char* idTexto;

    int overlap;

    ListaPosic posicL;
    ListaPosic posicR;
    ListaPosic posicC;
    ListaPosic posicT;
    ListaPosic selPosic;

    Reta lCmp;
    Retang rCmp;
    Circ cCmp;
    Texto tCmp;
    Coords nCoords;
    
    Circ nCirc;  

    double auxSelX;
    double auxSelY;
    double auxSelL;
    double auxSelA;
    double lAuxX1;
    double lAuxX2;
    double lAuxY1;
    double lAuxY2;
    double rAuxX;
    double rAuxY;
    double rAuxL;
    double rAuxA;
    double cAuxX;
    double cAuxY;
    double cAuxR;
    double tAuxX;
    double tAuxY;

    sprintf(id, "%d", idGen);
    sscanf(selX, "%lf", &auxSelX);
    sscanf(selY, "%lf", &auxSelY);
    sscanf(selL, "%lf", &auxSelL);
    sscanf(selA, "%lf", &auxSelA);

    strcpy(corB, "crimson");
    strcpy(corP, "crimson");
    strcpy(tipo, "r");
    sprintf(id, "%d", idGen);

    Retang retSel = criaRetang(selX, selY, selA, selL, corB, corP, id);
    insLista(retangulos, retSel); 
    Coords nCoord = criaCoords(id, selX, selY, tipo);
    insLista(coords, nCoord);

    idGen--;

    ListaPosic posic = primeiraPosicLista(coords);
    while(posic){
        Coords coordCmp = getLista(coords, posic);
        char* tipoCmp = getCoordTipo(coordCmp);
        switch(tipoCmp[0]){
            case 'l':
                coordIdL = getCoordID(coordCmp);
                posicL = primeiraPosicLista(retas);
                while(posicL){
                    lCmp = getLista(retas, posicL);
                    lId = getIDReta(lCmp);
                    selPosic = primeiraPosicLista(selecionadas);
                    overlap = 1;
                    while(selPosic){
                        nCoords = getLista(selecionadas, selPosic);
                        idReta = getCoordID(nCoords);
                        if(strcmp(lId, idReta) == 0){
                            overlap = 0;
                            break;
                        }
                        selPosic = prxPosicLista(selecionadas, selPosic);
                    }           
                    if(strcmp(lId, coordIdL) == 0 && overlap == 1){
                        lX1 = getX1Reta(lCmp);
                        lX2 = getX2Reta(lCmp);
                        lY1 = getY1Reta(lCmp);
                        lY2 = getY2Reta(lCmp);

                        sscanf(lX1, "%lf", &lAuxX1);
                        sscanf(lX2, "%lf", &lAuxX2);
                        sscanf(lY1, "%lf", &lAuxY1);
                        sscanf(lY2, "%lf", &lAuxY2);

                        if(lAuxX1 > auxSelX && lAuxX1 < (auxSelX + auxSelL) && lAuxX2 > auxSelX && lAuxX2 < (auxSelX + auxSelL) && lAuxY1 > auxSelY && lAuxY1 < (auxSelY + auxSelA) && lAuxY2 > auxSelY && lAuxY2 < (auxSelY + auxSelA)){
                            insLista(selecionadas, coordCmp);
                            strcpy(r, "1"); 
                            strcpy(tipo, "c");
                            sprintf(id, "%d", idGen);

                            nCirc = criaCirc(lX1, lY1, r, corB, corP, id);
                            nCoord = criaCoords(id, lX1, lY1, tipo);
                            idGen--; 

                            insLista(circulos, nCirc);
                            insLista(coords, nCoord);
                            strcpy(tipo, "Linha");
                            fprintf(txtFile, "A quantidade de figuras selecionadas: %d. Id e tipo da figura selecionada: Id %s Tipo %s\n", tamLista(selecionadas), getCoordID(nCoord), tipo);
                        } 
                    }
                    posicL = prxPosicLista(retas, posicL);
                }
                break;

            case 'r':
                coordIdR = getCoordID(coordCmp);
                posicR = primeiraPosicLista(retangulos);
                while(posicR){
                    rCmp = getLista(retangulos, posicR);
                    rId = getIDRetang(rCmp);
                    selPosic = primeiraPosicLista(selecionadas);
                    overlap = 1;
                    while(selPosic){
                        nCoords = getLista(selecionadas, selPosic);
                        idRetang = getCoordID(nCoords);
                        if(strcmp(rId, idRetang) == 0){
                            overlap = 0;
                            break;
                        }
                        selPosic = prxPosicLista(selecionadas, selPosic);
                    }
                    if(strcmp(rId, coordIdR) == 0 && overlap == 1){
                        rX = getXRetang(rCmp);
                        rY = getYRetang(rCmp);
                        rL = getLRetang(rCmp);
                        rA = getARetang(rCmp);

                        sscanf(rX, "%lf", &rAuxX);
                        sscanf(rY, "%lf", &rAuxY);
                        sscanf(rL, "%lf", &rAuxL);
                        sscanf(rA, "%lf", &rAuxA);

                        if(rAuxX > auxSelX && rAuxL < auxSelL && rAuxY > auxSelY && rAuxA < auxSelA){
                            insLista(selecionadas, coordCmp);

                            strcpy(r, "1");
                            strcpy(tipo, "c");
                            sprintf(id, "%d", idGen);
                            nCirc = criaCirc(rX, rY, r, corB, corP, id);
                            nCoord = criaCoords(id, rX, rY, tipo);
                            idGen--; 

                            insLista(circulos, nCirc);
                            insLista(coords, nCoord);
                            strcpy(tipo, "Retangulo");
                            fprintf(txtFile, "A quantidade de figuras selecionadas: %d. Id e tipo da figura selecionada: Id %s Tipo %s\n", tamLista(selecionadas), getCoordID(nCoord), tipo);

                        }
                    }
                    posicR = prxPosicLista(retangulos, posicR);      
                }
                break;

            case 'c':
                coordIdC = getCoordID(coordCmp);
                posicC = primeiraPosicLista(circulos);
                while(posicC){
                    cCmp = getLista(circulos, posicC);
                    cId = getIDCirc(cCmp);
                    selPosic = primeiraPosicLista(selecionadas);
                    int overlap = 1;
                    while(selPosic){
                        nCoords = getLista(selecionadas, selPosic);
                        idCirc = getCoordID(nCoords);
                        if(strcmp(cId, idCirc) == 0){
                            overlap = 0;
                            break;
                        }
                        selPosic = prxPosicLista(selecionadas, selPosic);
                    }
                    if(strcmp(cId, coordIdC) == 0 && overlap == 1){
                        cX = getXCirc(cCmp);
                        cY = getYCirc(cCmp);
                        cR = getRaioCirc(cCmp);
                        
                        sscanf(cX, "%lf", &cAuxX);
                        sscanf(cY, "%lf", &cAuxY);
                        sscanf(cR, "%lf", &cAuxR);

                        if((cAuxX - cAuxR) > auxSelX && (cAuxX + cAuxR) < (auxSelX + auxSelL) && (cAuxY - cAuxR) > auxSelY && (cAuxY + cAuxR) < (auxSelY + auxSelA)){
                            insLista(selecionadas, coordCmp);
                            

                            strcpy(r, "1");
                            strcpy(tipo, "c");
                            sprintf(id, "%d", idGen);
                            nCirc = criaCirc(cX, cY, r, corB, corP, id);
                            nCoord = criaCoords(id, cX, cY, tipo);
                            idGen--; 

                            insLista(circulos, nCirc);
                            insLista(coords, nCoord);
                            
                            fprintf(txtFile, "A quantidade de figuras selecionadas: %d. Id e tipo da figura selecionada: Id %s Tipo %s\n", tamLista(selecionadas), getCoordID(nCoord), tipo);

                        }
                    }
                    posicC = prxPosicLista(circulos, posicC);
                }

                break;

            case 't':
                coordIdT = getCoordID(coordCmp);
                posicT = primeiraPosicLista(textos);
                while(posicT){
                    tCmp = getLista(textos, posicT);
                    tId = getIDTexto(tCmp);
                    selPosic = primeiraPosicLista(selecionadas);
                    overlap = 1;
                    while(selPosic){
                        nCoords = getLista(selecionadas, selPosic);
                        idTexto = getCoordID(nCoords);
                        if(strcmp(tId, idTexto) == 0){
                            overlap = 0;
                            break;
                        }
                        selPosic = prxPosicLista(selecionadas, selPosic);
                    }
                    if(strcmp(tId, coordIdT) == 0 && overlap == 1){
                        tX = getXTexto(tCmp);
                        tY = getYTexto(tCmp);

                        sscanf(tX, "%lf", &tAuxX);
                        sscanf(tY, "%lf", &tAuxY);

                        if(tAuxX > auxSelX && tAuxX < (auxSelX + auxSelL) && tAuxY > auxSelY && tAuxY < (auxSelY + auxSelA)){
                            insLista(selecionadas, coordCmp); 

                            strcpy(r, "1");
                            strcpy(tipo, "c");
                            sprintf(id, "%d", idGen);
                            nCirc = criaCirc(tX, tY, r, corB, corP, id);
                            nCoord = criaCoords(id, tX, tY, tipo);
                            idGen--; 

                            insLista(circulos, nCirc);
                            insLista(coords, nCoord);
                            strcpy(tipo, "Texto");

                            fprintf(txtFile, "A quantidade de figuras selecionadas: %d. Id e tipo da figura selecionada: Id %s Tipo %s\n", tamLista(selecionadas), getCoordID(nCoord), tipo);
                        }
                    }
                    posicT = prxPosicLista(textos, posicT);      
                }
                break;

            default:
                break;    
        }
        posic = prxPosicLista(coords, posic);
    }
}

void dels(Lista coords, Lista selecionadas, Lista retangulos, Lista circulos, Lista retas, Lista textos){
    ListaPosic posicSel = primeiraPosicLista(selecionadas);
    while(posicSel){ 
        ListaPosic posicCoords = primeiraPosicLista(coords);
        ListaPosic posicReta = primeiraPosicLista(retas);
        ListaPosic posicRetang = primeiraPosicLista(retangulos);
        ListaPosic posicCirc = primeiraPosicLista(circulos);
        ListaPosic posicTexto = primeiraPosicLista(textos);
        Coords nSel = getLista(selecionadas, posicSel);
        Coords nCoord;
        Reta nReta;
        Retang nRetang;
        Circ nCirc;
        Texto nTexto;
        char* selTipo = getCoordTipo(nSel);
        char* selId = getCoordID(nSel);
        char* idReta;
        char* idRetang;
        char* idCirc;
        char* idTexto;
        char* idCoord;
        switch(selTipo[0]){
            case 'l':
                while(posicReta){
                    nReta = getLista(retas, posicReta);
                    idReta = getIDReta(nReta);
                    if(strcmp(selId, idReta) == 0){
                        removeLista(retas, posicReta);
                        while(posicCoords){
                            nCoord = getLista(coords, posicCoords);
                            idCoord = getCoordID(nCoord);
                            if(strcmp(idCoord, selId) == 0){
                                removeLista(coords, posicCoords);
                                break;
                            }
                            posicCoords = prxPosicLista(coords, posicCoords);
                        }
                        break;
                    }
                    posicReta = prxPosicLista(retas, posicReta);
                }  
                break;

            case 'r':
                while(posicRetang){
                    nRetang = getLista(retangulos, posicRetang);
                    idRetang = getIDRetang(nRetang);
                    if(strcmp(selId, idRetang) == 0){
                        removeLista(retangulos, posicRetang);
                        while(posicCoords){
                            nCoord = getLista(coords, posicCoords);
                            idCoord = getCoordID(nCoord);
                            if(strcmp(idCoord, selId) == 0){
                                removeLista(coords, posicCoords);
                                break;
                            }
                            posicCoords = prxPosicLista(coords, posicCoords);
                        }
                        break;
                    }
                    posicRetang = prxPosicLista(retangulos, posicRetang);
                } 
                break;

            case 'c':
                    while(posicCirc){
                    nCirc = getLista(circulos, posicCirc);
                    idCirc = getIDCirc(nCirc);
                    if(strcmp(selId, idCirc) == 0){
                        removeLista(circulos, posicCirc);
                        while(posicCoords){
                            nCoord = getLista(coords, posicCoords);
                            idCoord = getCoordID(nCoord);
                            if(strcmp(idCoord, selId) == 0){
                                removeLista(coords, posicCoords);
                                break;
                            }
                            posicCoords = prxPosicLista(coords, posicCoords);
                        }
                        break;
                    }
                    posicCirc = prxPosicLista(circulos, posicCirc);
                } 
                break;

            case 't':
                    while(posicTexto){
                    nTexto = getLista(textos, posicCirc);
                    idTexto = getIDTexto(nTexto);
                    if(strcmp(selId, idTexto) == 0){
                        removeLista(textos, posicTexto);
                        while(posicCoords){
                            nCoord = getLista(coords, posicCoords);
                            idCoord = getCoordID(nCoord);
                            if(strcmp(idCoord, selId) == 0){
                                removeLista(coords, posicCoords);
                                break;
                            }
                            posicCoords = prxPosicLista(coords, posicCoords);
                        }
                        break;
                    }
                    posicTexto = prxPosicLista(textos, posicTexto);
                } 
                break;
        }
        posicSel = prxPosicLista(selecionadas, posicSel);
    }
    
}

// void pol(){
    
// }

// void dps(){
    
// }

// void ups(){
    
// }

void  leQry(char* BED, char* BSD, char* qry, char* geo, Lista retangulos, Lista circulos, Lista textos, Lista retas, Lista selecionadas, Fila corrente, Lista coords){
    if( BED == NULL || BSD == NULL || qry == NULL || retangulos == NULL || circulos == NULL || textos == NULL || retas == NULL || selecionadas == NULL || corrente == NULL){
        return;
    }

    int tamBED = strlen(BED);
    int tamQry = strlen(qry);

    int temBarra = BED[tamBED-1] == '/';

    char* qryCaminho = malloc(tamBED + tamQry + 1 + !temBarra);

    if(qryCaminho == NULL){
        return;
    }

    if(temBarra){
        sprintf(qryCaminho, "%s%s", BED, qry);
    } else{
        sprintf(qryCaminho, "%s/%s", BED, qry);
    }
    
    FILE* qryFile = (fopen(qryCaminho, "r"));

    free(qryCaminho);

    char* geoNome = strtok(geo, ".");
    char* qryNome = strtok(qry, ".");
    qryNome = strrchr(qryNome, '/')+1;
    int tamBSD = strlen(BSD);
    temBarra = BSD[tamBSD-1] == '/';

    char* svgNome = malloc(tamBSD + strlen(geoNome) + strlen(qryNome) + 6 + !temBarra);
    char* txtNome = malloc(tamBSD + strlen(geoNome) + strlen(qryNome) + 6 + !temBarra);

    if(temBarra){
        sprintf(svgNome, "%s%s-%s.svg", BSD, geoNome, qryNome);
    } else{
        sprintf(svgNome, "%s/%s-%s.svg", BSD, geoNome, qryNome);
    }

    if(temBarra){
        sprintf(txtNome, "%s%s-%s.txt", BSD, geoNome, qryNome);
    } else{
        sprintf(txtNome, "%s/%s-%s.txt", BSD, geoNome, qryNome);
    }

    FILE* svg = fopen(svgNome,"w");
    fprintf(svg, "<svg>\n");

    // Fila filas[10];
    // Lista listas[10];
    // ListaPosic registradores[10];

    // for(int i = 0; i < 10; i++){
    //     filas[i] = criaFila();
    //     listas[i] = criaLista();
    //     registradores[i] = NULL;
    // }

    FILE* txtFile = (fopen(txtNome, "w"));

    char aux[999];    

    while(1){
        fgets(aux, 999, qryFile);
        if(feof(qryFile)){
            break;
        }

        if(aux[strlen(aux)-1] == '\n'){
            aux[strlen(aux)-1] = '\0';
        }
        
        char* arg = strtok(aux, " ");

        if(strcmp(arg, "inp") == 0){
            inp(coords, corrente);
            continue;
        }

        if(strcmp(arg, "rmp") == 0){
            rmp(txtFile, corrente);
            continue;
        }

        if(strcmp(arg, "clp") == 0){
            clp(corrente);
            continue;

        }

        if(strcmp(arg, "sel") == 0){
            sel(txtFile, coords, selecionadas, retangulos, circulos, retas, textos);
            continue;

        }

        if(strcmp(arg, "sel+") == 0){
            selM(txtFile, coords, selecionadas, retangulos, circulos, retas, textos);
            continue;
        }

        if(strcmp(arg, "dels") == 0){
            dels(coords, selecionadas, retangulos, circulos, retas, textos);
            continue;
        }

        // nesse ponto minha ansiedade venceu e nao consegui mais ser produtivo, mesmo com medicacao.

        // if(strcmp(arg, "pol") == 0){
            
        //     continue;

        // }

        // if(strcmp(arg, "dps") == 0){

        //     continue;
        // }

        // if(strcmp(arg, "ups") == 0){

        //     continue;
        // }
    }
        

    ListaPosic posic = primeiraPosicLista(retangulos);
    while(posic){
        Retang retang = getLista(retangulos, posic);
        retangSvg(svg, retang);
        posic = prxPosicLista(retangulos, posic);
    }

    posic = primeiraPosicLista(circulos);
    while(posic){
        Circ circ = getLista(circulos, posic);
        circSvg(svg, circ);
        posic = prxPosicLista(circulos, posic);
    }

    posic = primeiraPosicLista(textos);
    while(posic){
        Texto texto = getLista(textos, posic);
        textoSvg(svg, texto);
        posic = prxPosicLista(textos, posic);
    }

    posic = primeiraPosicLista(retas);
    while(posic){
        Reta reta = getLista(retas, posic);
        retaSvg(svg, reta);
        posic = prxPosicLista(retas, posic);
    }

    fprintf(svg, "</svg>");
}