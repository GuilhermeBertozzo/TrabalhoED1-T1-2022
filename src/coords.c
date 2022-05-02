#include "coords.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct coords{
    char* id;
    char* x;
    char* y;
    char* tipo;
};

Coords criaCoords(char* id, char* x, char* y, char* tipo){
    Coords nCoord = malloc(sizeof(struct coords));

    if(nCoord == NULL){
        return NULL;
    }

    nCoord->id = malloc(strlen(id)+1);
    nCoord->x = malloc(strlen(x)+1);
    nCoord->y = malloc(strlen(y)+1);
    nCoord->tipo = malloc(strlen(tipo)+1);

    strcpy(nCoord->id, id);
    strcpy(nCoord->x, x);
    strcpy(nCoord->y, y);
    strcpy(nCoord->tipo, tipo);

    if(nCoord->id == NULL || nCoord->x == NULL || nCoord->y == NULL || nCoord->tipo == NULL){
        return NULL;
    }

    return nCoord;
}

char* getCoordX(Coords coords){
    if(coords == NULL){
        return NULL;
    }

    return coords->x; 
}

char* getCoordY(Coords coords){
    if(coords == NULL){
        return NULL;
    }

    return coords->y;  
}

char* getCoordID(Coords coords){
    if(coords == NULL){
        return NULL;
    }

    return coords->id;
}

char* getCoordTipo(Coords coords){
    if(coords == NULL){
        return NULL;
    }

    return coords->tipo;
}

void desfazCoord(Coords coords){
    if(coords == NULL){
        return;
    }

    if(coords->x){
        free(coords->x);
    }
    if(coords->y){
        free(coords->y);
    }
    if(coords->tipo){
        free(coords->tipo);
    }
    if(coords->id){
        free(coords->id);
    }

    free(coords);
}
