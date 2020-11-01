#include "FunMain.h"

void lowerCase (char* str){
	for(int i=0; str[i]!='\0'; i++){
		str[i] = tolower(str[i]);
	}
}

void removeSpacesInPlace (char* str) {

	size_t str_len = strlen(str); // para tener strlen se debe incluir <string.h>
	char result [str_len];
	size_t p = 0;

	size_t i = 0;
	for (i = 0; i < str_len; ++i) {
		if (str[i] != ' ') {
			// result necesita su propio posicionador o iremos dejando agujeros
			result[p] = str[i];

			// Sólo avanzamos la posición p si se realiza la inserción
			p++;
		}
	}

	// funciones como printf buscan el caracter 0
	// aunque dejamos str con el mismo tamaño en memoria, ponemos la
	// marca de fin de la cadena en donde corresponde
	if (p < str_len)
		str[p] = '\0';

	// Reescribimos str con el contenido de result
	for (i = 0; i < p; ++i) {
		str[i] = result[i];
	}
}

//------------------------------------------------------------

bool stringSearchList( Lista* L, const char* nombreC ){
    Camino* auxC = firstL( L );
    while( auxC != NULL){
        if( strcmp( auxC->ciudad_adj->clave, nombreC ) == 0 ){
            return true;
        }
        auxC = nextL( L );
    }
    return false;
}

void ListaOrdenadaInt( Lista* L, Camino* C){
    Camino* auxC = firstL( L );
    while(auxC != NULL){
        if( C->distancia < auxC->distancia ){
            pushCurrentL( L, C);
            return;
        }
        auxC = nextL( L );
    }
    pushBackL( L, C);
}

void* PosLista( Lista* L, int pos){
    if( pos == 0 ){
        return firstL(L);
    }
    void* aux = firstL(L);
    for(int i=0 ; i< pos; i++){
        aux = nextL(L);
    }

    return aux;
}

//------------------------------------------------------------

void generarCaminos( Ciudad* C1, Ciudad* C2, int distancia){
    //se crean las interconexiones
    Camino* newCa1 = crearCamino(C2, distancia);
    ListaOrdenadaInt(C1->caminos, newCa1);

    Camino* newCa2 = crearCamino(C1, distancia);
    ListaOrdenadaInt(C2->caminos, newCa2);
}

void mostrarRuta( Lista* ruta ){

    int recorrido = 0;
    printf("\n\t\tRUTA CREADA\n\n");

    printf("   ");
    Ciudad* auxC = firstL(ruta);
    while(auxC != NULL){
        printf("%s", auxC->nombre);

        //obtiene la distancia de la ciudad actual a la anterior
        Ciudad* ant = prevL(ruta);
        if( ant != NULL ){

            auxC = nextL(ruta);

            Camino* C = firstL(auxC->caminos);
            while( C != NULL ){
                if(strcmp(C->ciudad_adj->clave, ant->clave) == 0){
                    recorrido += C->distancia;
                    break;
                }
                C = nextL(auxC->caminos);
            }
        }

        auxC = nextL(ruta);

        if( auxC == NULL ){
            printf(".\n");
        }else{
            printf(" -> ");
        }
    }
    printf("   Kilometros Recorridos : %d km\n", recorrido);
}

int distanciaRuta( Lista* ruta ){
    int recorrido = 0;

    Ciudad* auxC = firstL(ruta);
    while(auxC != NULL){

        //obtiene la distancia de la ciudad actual a la anterior
        Ciudad* ant = prevL(ruta);
        if( ant != NULL ){

            auxC = nextL(ruta);

            Camino* C = firstL(auxC->caminos);
            while( C != NULL ){
                if(strcmp(C->ciudad_adj->clave, ant->clave) == 0){
                    recorrido += C->distancia;
                    break;
                }
                C = nextL(auxC->caminos);
            }
        }

        auxC = nextL(ruta);
    }

    return recorrido;
}

void obtenerRuta( Lista* RutaActual, Lista* MejorRuta, Ciudad* Destino ){
    CPos* origen = firstL( RutaActual );
    int PF = origen->ciudad->caminos->total;
    bool flag;

    while( origen->posL < PF ){
        CPos* ultimo = lastL( RutaActual );

        //obtiene la ciudad siguiente en la lista de caminos de la ultima ciudad de la ruta
        Camino* camino = PosLista( ultimo->ciudad->caminos, ultimo->posL);
        if( camino == NULL){
            deleteBackL(RutaActual);
            ultimo = lastL(RutaActual);
            ultimo->posL++;
            continue;
        }

        Ciudad* C_adj = camino->ciudad_adj;

        flag = false;

        //ver si la ciudad no este en la ruta actual
        CPos* opc = firstL(RutaActual);
        while(opc != NULL){
            if( strcmp( C_adj->clave, opc->ciudad->clave) == 0 ){
                flag = true;
                break;
            }
            opc = nextL(RutaActual);
        }
        if( flag ){
            ultimo->posL++;
            continue;
        }

        //insertar la ciudad a la ruta actual
        CPos* newCP = crearCPos( C_adj );
        pushBackL(RutaActual, newCP);

        //verificar distancias
        if( MejorRuta->total != 0 ){
            Lista* auxL = crearLista();

            opc = firstL(RutaActual);
            while( opc != NULL){
                pushBackL(auxL, opc->ciudad);
                opc = nextL(RutaActual);
            }

            int MR = distanciaRuta(MejorRuta);
            int RA = distanciaRuta(auxL);

            deleteL(auxL);
            free(auxL);

            if( RA > MR ){
                deleteBackL(RutaActual);
                ultimo = lastL(RutaActual);
                ultimo->posL++;
                continue;
            }
        }

        //verificar si la ultima ciudad es el destino
        if( strcmp(newCP->ciudad->clave, Destino->clave ) == 0 ){
            deleteL(MejorRuta);

            opc = firstL(RutaActual);
            while( opc != NULL){
                pushBackL(MejorRuta, opc->ciudad);
                opc = nextL(RutaActual);
            }

            //mostrarRuta( MejorRuta ); era para ver los posibles caminos

            deleteBackL(RutaActual);
            ultimo = lastL(RutaActual);
            ultimo->posL++;
            continue;
        }
    }
}

//------------------------------------------------------------

void ImportarArchivo( Mapa* grafo){
    system("cls");

    char archivo[max], C1[max], C2[max], clave_1[max], clave_2[max] ;
    int distancia = -1;

    printf("\n\t\tIMPORTAR CIUDADES\n\n");

  	printf("   Nombre del archivo(sin.csv): ");
  	gets( archivo );
  	strcat(archivo,".csv");

  	FILE* CIUDADES = fopen( archivo, "r");

    if( CIUDADES == NULL ){
        printf("\n   Archivo NO existe\n\n");
    }else{
        char linea[1024];
        printf("\n   Procesando archivo...\n");

        while( fgets(linea, 1023, CIUDADES) != NULL ){
            const char* ciudad1 = get_csv_field( linea, 0);
            const char* ciudad2 = get_csv_field( linea, 1);
            distancia = atoi( get_csv_field(linea, 2) );

            //evita warnings
            strcpy(C1, ciudad1);
            strcpy(C2, ciudad2);

            removeSpacesInPlace(C1);
            removeSpacesInPlace(C2);

            if( ( strcmp(C1,"") != 0 )&&( strcmp(C2,"") != 0 )&&( distancia > 0 ) ){

                strcpy(clave_1, C1);
                strcpy(clave_2, C2);

                lowerCase(clave_1);
                lowerCase(clave_2);

                Ciudad* auxC1 = searchMap( grafo, clave_1);
                Ciudad* auxC2 = searchMap( grafo, clave_2);

                if( auxC1 == NULL ){
                    Ciudad* newC1 = crearCiudad( C1, clave_1 );

                    if( auxC2 == NULL ){
                        Ciudad* newC2 = crearCiudad( C2, clave_2 );

                        generarCaminos( newC1, newC2, distancia);

                        //insertar las ciudades al mapa
                        insertMap(grafo, newC1->clave, newC1);
                        insertMap(grafo, newC2->clave, newC2);

                    }else{


                        generarCaminos( newC1, auxC2, distancia);

                        //insertar las ciudades al mapa
                        insertMap(grafo, newC1->clave, newC1);

                    }
                }else{

                    if( auxC2 == NULL ){
                        Ciudad* newC2 = crearCiudad( C2, clave_2 );

                        generarCaminos( auxC1, newC2, distancia);

                        //insertar las ciudades al mapa
                        insertMap(grafo, newC2->clave, newC2);

                    }else{

                        if( stringSearchList( auxC1->caminos, clave_2) == false ){

                            generarCaminos( auxC1, auxC2, distancia);

                        }
                    }
                }
            }
        }

        printf("   Archivo finalizado\n");
    }

    printf("\n");
    system("pause");
}

void CiudadCercana( Mapa* grafo){
    system("cls");

    char ciudad[max];

    printf("\n\t\tCIUDADES MAS CERCANAS\n\n");

    printf("    Nombre Ciudad    : ");
    gets(ciudad);

    removeSpacesInPlace(ciudad);
    lowerCase(ciudad);

    Ciudad* auxC = searchMap(grafo, ciudad);

    if( auxC == NULL){
        printf("\n   -ERROR::Ciudad NO Existe\n");
    }else{
        Lista* auxL = auxC->caminos;
        printf("\n   Las Ciudades Cercanas son:\n\n");
        printf("   ");

        Camino* cam = firstL(auxL);
        printf("%s", cam->ciudad_adj->nombre);
        /*
        while(cam != NULL){
            printf("%s", cam->ciudad_adj->nombre);
            cam = nextL(auxL);
            if(cam != NULL){
                printf(", ");
            }else{
                printf(".\n");
            }
        }
        */
    }

    printf("\n");
    system("pause");
}

void CrearRuta( Mapa* grafo ){
    system("cls");

    char ciudad[max];
    Lista* ruta = crearLista();

    printf("\n\t\tCREAR RUTA\n\n");

    printf("    Ciudad de Origen   : ");
    gets(ciudad);

    removeSpacesInPlace(ciudad);
    lowerCase(ciudad);

    Ciudad* auxC = searchMap(grafo, ciudad);

    if( auxC == NULL){
        printf("\n   -ERROR::Ciudad de Origen NO Existe\n");
    }else{
        bool flag = true;
        char pregunta[max];
        pushBackL(ruta, auxC);

        do{

            //mostrar Ciudades crecanas
            printf("\n   Ciudades cercanas a %s : \n", auxC->nombre );
            Lista* auxL = auxC->caminos;

            printf("   ");
            Camino* cam = firstL(auxL);
            while(cam != NULL){
                /*
                    //cuando se hace la ruta no muestra la ciudad de donde vino.
                    Ciudad* ult = lastL(ruta);
                    ult = prevL(ruta);
                    if(ult != NULL){
                        if(strcmp(ult->clave, cam->ciudad_adj->clave) != 0){
                            printf("%s", cam->ciudad_adj->nombre);
                        }else{
                            cam = nextL(auxL);
                            continue;
                        }
                    }else{
                        printf("%s", cam->ciudad_adj->nombre);
                    }
                */
                printf("%s", cam->ciudad_adj->nombre);
                cam = nextL(auxL);
                if(cam != NULL){
                    printf(", ");
                }else{
                    printf(".\n");
                }
            }

            //pregunta la siguiente ciudad y si no existe vuelve a preguntar hasta que este en la ruta o la termine
            do{
                printf("\n    Ciudad Siguiente  : ");
                gets(ciudad);

                removeSpacesInPlace(ciudad);
                lowerCase(ciudad);

                if( stringSearchList(auxL, ciudad ) ){
                    auxC = searchMap(grafo, ciudad);
                    printf("\n   -Ciudad Confirmada" );
                    pushBackL(ruta, auxC);
                    break;
                }else{
                    printf("\n   -Esta Ciudad no esta en la Ruta" );
                    printf("\n   -Desea terminar la ruta?(si/no) : ");
                    gets(pregunta);
                    removeSpacesInPlace(pregunta);
                    lowerCase(pregunta);

                    if(strcmp(pregunta, "si") == 0){
                        flag = false;
                        break;
                    }
                }
            }while(true);

            if(flag == false){
                break;
            }

            printf("\n   -Desea terminar la ruta?(si/no) : ");
            gets(pregunta);
            removeSpacesInPlace(pregunta);
            lowerCase(pregunta);

            if(strcmp(pregunta, "si") == 0){
                flag = false;
            }

        }while(flag);

        system("cls");
        mostrarRuta( ruta );
    }
    printf("\n");
    system("pause");
}

void RutaCorta( Mapa* grafo ){
    system("cls");

    char origen[max], destino[max];

    printf("\n\tRUTA MAS CORTA ENTRE CIUDADES\n\n");

    printf("    Ciudad de Origen   : ");
    gets(origen);
    printf("    Ciudad de Destino  : ");
    gets(destino);

    removeSpacesInPlace(origen);
    removeSpacesInPlace(destino);
    lowerCase(origen);
    lowerCase(destino);

    Ciudad* origen_C = searchMap(grafo, origen);
    Ciudad* destino_c = searchMap(grafo, destino);

    if( origen_C == NULL || destino_c == NULL ){
        printf("\n   -ERROR::Ciudad de Origen o Destino NO existen\n");
    }else{
        Lista* MejorRuta = crearLista();
        Lista* RutaActual = crearLista();

        CPos* origenP = crearCPos( origen_C );
        pushBackL(RutaActual, origenP);

        obtenerRuta( RutaActual, MejorRuta, destino_c );

        mostrarRuta( MejorRuta );

    }

    printf("\n");
    system("pause");
}

void Circuito( Mapa* grafo ){
    system("cls");

    char origen[max], segunda[max], tercera[max];

    printf("\n\t\tCIRCUITO ENTRE CIUDADES\n\n");

    printf("    Primera Ciudad   : ");
    gets(origen);
    printf("    Segunda Ciudad   : ");
    gets(segunda);
    printf("    Tercera Ciudad   : ");
    gets(tercera);

    removeSpacesInPlace(origen);
    removeSpacesInPlace(segunda);
    removeSpacesInPlace(tercera);

    lowerCase(origen);
    lowerCase(segunda);
    lowerCase(tercera);

    Ciudad* C1 = searchMap(grafo, origen);
    Ciudad* C2 = searchMap(grafo, segunda);
    Ciudad* C3 = searchMap(grafo, tercera);

    if( C1 == NULL || C2 == NULL || C3 == NULL ){
        printf("\n   -ERROR::Algunas Ciudades NO existen\n");
    }else{
        Lista* CircuitoL = crearLista();
        Lista* Movimiento = crearLista();
        Lista* aux = crearLista();

        //obtengo de C1 - C2
        CPos* inicioP = crearCPos( C1 );
        pushBackL(Movimiento, inicioP);

        obtenerRuta( Movimiento, CircuitoL, C2);

        //obtengo de C2- C3
        deleteL(Movimiento);
        inicioP = crearCPos( C2 );
        pushBackL(Movimiento, inicioP);

        obtenerRuta( Movimiento, aux, C3);

        Ciudad* auxC = firstL(aux);
        auxC = nextL(aux);
        while(auxC != NULL){
            pushBackL(CircuitoL, auxC);
            auxC = nextL(aux);
        }

        //obtengo de C3 - C1
        deleteL(aux);
        deleteL(Movimiento);
        inicioP = crearCPos( C3 );
        pushBackL(Movimiento, inicioP);

        obtenerRuta( Movimiento, aux, C1);

        auxC = firstL(aux);
        auxC = nextL(aux);
        while(auxC != NULL){
            pushBackL(CircuitoL, auxC);
            auxC = nextL(aux);
        }

        //se muestra el circuito
        mostrarRuta(CircuitoL);
    }

    printf("\n");
    system("pause");
}
