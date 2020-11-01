#ifndef CIUDAD_H
#define CIUDAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TDA&CSV/Lista.h"

#define max 100

typedef struct{
    char nombre[max];
    char clave[max];
    Lista* caminos;
}Ciudad;

typedef struct{
    Ciudad* ciudad_adj;
    int distancia;
}Camino;

typedef struct{
    Ciudad* ciudad;
    int posL;
}CPos;

Ciudad* crearCiudad( const char* nombre, const char* clave);

Camino* crearCamino( Ciudad* newC, int distancia);

CPos* crearCPos( Ciudad* newC );

#endif // CIUDAD_H
