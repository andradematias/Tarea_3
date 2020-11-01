#ifndef FUNMAIN_H
#define FUNMAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <stdbool.h>

#include "TDA&CSV/Mapa.h"
#include "TDA&CSV/Lista.h"
#include "TDA&CSV/CSV.h"
#include "Ciudad.h"

#define max 100

void lowerCase (char* str);

void removeSpacesInPlace (char* str);

//-----------------------------------------------------

bool stringSearchList( Lista* L, const char* nombreC );

void ListaOrdenadaInt( Lista* L, Camino* C);

//-----------------------------------------------------

void generarCaminos( Ciudad* C1, Ciudad* C2, int distancia);

void mostrarRuta( Lista* ruta );

int distanciaRuta( Lista* ruta );

void obtenerRuta( Lista* RutaActual, Lista* MejorRuta, Ciudad* Destino );

//-----------------------------------------------------

void ImportarArchivo( Mapa* grafo );

void CiudadCercana( Mapa* grafo );

void CrearRuta( Mapa* grafo );

void RutaCorta( Mapa* grafo );

void Circuito( Mapa* grafo );

#endif
