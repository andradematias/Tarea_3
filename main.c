#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "Mapa.h"
#include "FunMain.h"

#define min 20

int main(){
    system("COLOR A");

    Mapa* grafo = crearMapa(min);

    int opcion;

    do{
        system("cls");
        printf("\n\t\tGPS\n\n");

        printf("   1-.Importar Ciudades desde un Archivo\n");
        printf("   2-.Ciudad mas cercana\n");
        printf("   3-.Crear ruta\n");
        printf("   4-.Ruta mas corta entre Ciudades\n");
        printf("   5-.Mejor Circuito\n");
        printf("   6-.Salir\n");
        printf("   Opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch(opcion){
            case 1:
                ImportarArchivo( grafo );
            break;
            case 2:
                CiudadCercana( grafo );
            break;
            case 3:
                CrearRuta( grafo );
            break;
            case 4:
                RutaCorta( grafo );
            break;
            case 5:
                Circuito( grafo );
            break;
        }
        if( opcion != 6){  //para que no guarde la ultima eleccion
            opcion = 0;
        }
    }while( opcion != 6);

    return 0;
}
