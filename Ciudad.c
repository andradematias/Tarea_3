#include "Ciudad.h"

Ciudad* crearCiudad( const char* nombre, const char* clave){
    Ciudad* newC = (Ciudad*)malloc(sizeof(Ciudad));

    strcpy(newC->nombre, nombre);
    strcpy(newC->clave, clave);

    Lista* newL = crearLista();
    newC->caminos = newL;

    return newC;
}

Camino* crearCamino( Ciudad* newC, int distancia){
    Camino* newCa = (Camino*)malloc(sizeof(Camino));

    newCa->ciudad_adj = newC;
    newCa->distancia = distancia;

    return newCa;
}

CPos* crearCPos( Ciudad* newC ){
    CPos* newCP = (CPos*)malloc(sizeof(CPos));

    newCP->ciudad = newC;
    newCP->posL = 0;

    return newCP;
}
