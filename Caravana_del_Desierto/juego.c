#include "juego.h"
#include "tablero.h"
#include "lista.h"
#include "animacion.h"

void menu(tConfig *c)
{
    unsigned opcion;

    do
    {
        printf("------CARAVANA DEL DESIERTO------\n\n");
        printf("Seleccione la opcion deseada:\n");
        printf("1 - Iniciar partida\n");
        printf("2 - Ver ranking\n");
        printf("3 - Salir\n");
        //4 - configurar partida

        opcion = ingresar(TAM_OP);

        while(!opcionValida(opcion))
        {
            printf("Ingrese una opcion valida: ");
            opcion = ingresar(TAM_OP);
        }

        ejecutarOpcion(opcion,c);

        system("pause");
        system("cls");
    }
    while(opcion != SALIR);

}

int opcionValida(unsigned op)
{
    return op >= OPCION1 && op <= SALIR;
}

int ingresar(unsigned tam)
{
    char ingreso[tam];
    fgets(ingreso,tam,stdin);
    if (strchr(ingreso, '\n') == NULL)
    {
        while (getchar() != '\n');
    }
    return atoi(ingreso);
}

void ejecutarOpcion(unsigned opcion,tConfig* c)
{
   switch (opcion)
    {
    case 1:
        system("cls");
        registrarJugador();
        iniciarPartida(c);
        break;

    case 2:
        system("cls");
//        casoPruebaBIN(ARCH_PARTIDAS);///ELMINAR ESTE ARCHIVO, ES SOLO PARA PROBAR EL RANKING
        mostrarRanking(ARCH_PARTIDAS);
        break;

    case 3:
        break;
    }
}

void registrarJugador()
{
    char nombreJugador[100];
    printf("\nIngrese su nombre: ");
    scanf(" %[^\n]",nombreJugador); // [^\n] permite leer espacios hasta presionar Enter y El espacio antes de % es limpia cualquier '\n' pendiente en el buffer

    // identificarJugador(); //funcion de jugador.h donde se hace la gestion de jugadores(no seria lo mismo que el jugador del juego)

    printf("\nBienvenido/a %s\n", nombreJugador);

}

void iniciarPartida(tConfig *c)
{
    tCola colaMovimiento; //HACER
    tJugador jugador;
    tMovimiento movimiento;
    /*implementacion TXT*/
    tListaD ruta;
    tNodoD *nodoJugador = NULL, *nodoCampamento;
    int dado,game_over = 1,turno =1,enter;
    char dir;
    tBandido bandidos[c->maximo_bandidos];
    iniciarCaracteristicasJugador(&jugador,c);
    crearListaD(&ruta);
    crearCola(&colaMovimiento);

    if(!generarTablero(c, &ruta))
        printf("no se pudo generar el tablero\n");


        ///probar
    posicionarBandidosEnRuta(bandidos,&ruta); //guarda la direccion de cada bandido en la ruta


    nodoJugador = posicionarJugadorEnInicio(&ruta); //poner a jugador en I --> poner [I J]
    nodoCampamento = nodoJugador;

    while(jugador.vidas != 0 && game_over)
    {

        printf("\n");
        printf("+===========================================================+\n");
        printf("|              CARAVANA DEL DESIERTO  ~  Dia %-2d             |\n", turno);
        printf("+===========================================================+\n");
        printf("Vidas: %d | Puntos: %d | Protegido: %s\n",
               jugador.vidas, jugador.puntos, jugador.protegido ? "Si" : "No");
        printf("\n");
        recorrerListaDobleIzqADer(&ruta,mostrarTablero);
        printf("\n");

        if(jugador.pierdeTurno)
        {
            printf("Perdes este turno por la Tormenta de Arena!\n");
            jugador.pierdeTurno = 0;
            printf("Presiona 0 para continuar...");
            scanf(" %d",&enter);
            system("cls");
            printf("+===========================================================+\n");
            printf("|          CARAVANA DEL DESIERTO  ~  Resultado Dia %-2d      |\n", turno);
            printf("+===========================================================+\n\n");
            printf("Una lagartija te alquilo la cueva por 2 monedas de oro\n");
            turno++;
        }
        else
        {
            //TURNO JUGADOR
            dado = tirarDado();
            printf("+===========================================================+\n");
            printf("|                  Tiraste el dado:          %d              |\n", dado);
            printf("+===========================================================+\n\n");
            printf("Hacia donde queres moverte? (A = Avanzar / R = Retroceder): ");
            scanf(" %c", &dir);
            while(dir != 'A' && dir != 'R')
            {
                printf("Direccion invalida. Ingresa A o R: ");
                scanf(" %c", &dir);
            }
            guardarMovimiento(&movimiento,nodoJugador,dir,dado,'J');
            encolar(&colaMovimiento,&movimiento,sizeof(tMovimiento));

            //TURNO DE LOS BANDIDOS
            dado = tirarDado();
            printf("+===========================================================+\n");
            printf("|                  Los bandidos tiraron el dado:       %d    |\n", dado);
            printf("+===========================================================+\n\n");
            printf("Cuidado, trataran de atraparte.\n");
            determinarMovimientosBandidos(bandidos,c->maximo_bandidos,nodoJugador,&colaMovimiento,dado);
            system("pause");

            while(colaVacia(&colaMovimiento) == COLA_NOVACIA)
            {
                desencolar(&colaMovimiento,&movimiento,sizeof(tMovimiento));
                if(movimiento.tipoJugador == 'J' )
                    nodoJugador = moverJugador(nodoJugador, movimiento.pasos, movimiento.direccion);
                else
                    moverBandidos(bandidos,&movimiento, c->maximo_bandidos);

            }
            system("cls");
            printf("+===========================================================+\n");
            printf("|                Posiciones tras los movimientos:            |\n");
            printf("+===========================================================+\n\n");
            recorrerListaDobleIzqADer(&ruta, mostrarTablero);
            printf("\n\n");
            system("pause");

            system("cls");
            printf("+===========================================================+\n");
            printf("|          CARAVANA DEL DESIERTO  ~  Resultado Dia %-2d      |\n", turno);
            printf("+===========================================================+\n\n");


            if(analizarJuego(nodoJugador, &jugador, nodoCampamento, &nodoJugador,bandidos, c->maximo_bandidos) == GAME_OVER)
                game_over = 0;

            turno++;
        }

    }

    system("cls");
    if(jugador.vidas == 0)
        printf("Perdiste! Puntos finales: %d\n", jugador.puntos);
    else
    {
        printf("=== VICTORIA! ===\n");
        printf("Puntos conseguidos: %d | Vidas sobrantes: %d\n", jugador.puntos, jugador.vidas);
    }

    //mostrarHistorial(); //mostrar los movimientos hechos durante la partida
    //guardarPartida(); // en partidas.dat

}

int tirarDado()
{
    return(rand() % 6 + 1);
}

int analizarJuego(tNodoD *nodo, tJugador *jugador, tNodoD *nodoInicio,tNodoD** nodoJugador,tBandido* bandidos, int cantB)
{
    tCasilla *cas = (tCasilla*)nodo->dato;
    int resultado = EXITO;

    if (cas->tieneB > 0)
    {
        if (jugador->protegido)
        {
            printf("Bandido! Pero el Oasis te protegio.\n");
            jugador->protegido = 0;
        }
        else
        {
            jugador->vidas--;
            if (jugador->vidas == 0)
            {
                printf("Un Bandido te atrapo! No tenes mas vidas. Fin de la partida.\n");
                resultado = GAME_OVER;
            }
            else
            {
                ((tCasilla*)nodo->dato)->tieneJ = 0;
                ((tCasilla*)nodoInicio->dato)->tieneJ = 1;
                *nodoJugador = nodoInicio;

                cas->tieneB--; // El bandido es eliminado del tablero
                eliminarBandido(bandidos,cantB,nodo); //Elimina al bandido del vector
                printf("Un Bandido te atrapo! Perdes una vida. Vidas: %d. Volviste al Campamento Inicial.\n", jugador->vidas);
            }
        }
    }
    else
    {
        switch (cas->tipo)
        {
            case '.':
                printf("Fue un dia tranquilo como para tomar mates y comer chipas...\n");
                break;
            case 'P':
                jugador->puntos++;
                printf("Capturaste un Premio! Puntos: %d\n", jugador->puntos);
                cas->tipo = '.';
                break;
            case 'V':
                jugador->vidas++;
                printf("Capturaste una Vida Extra! Vidas: %d\n", jugador->vidas);
                cas->tipo = '.';
                break;
            case 'O':
                jugador->protegido = 1;
                printf("Llegaste a un Oasis! Estas protegido el proximo turno.\n");
                break;
            case 'T':
                if (jugador->protegido)
                {
                    printf("Tormenta de Arena! Pero el Oasis te protegio.\n");
                    jugador->protegido = 0;
                }
                else
                {
                    jugador->pierdeTurno = 1;
                    printf("Tormenta de Arena! Perdes el proximo turno.\n");
                }
                break;
            case 'S':
                printf("Llegaste a la Salida! Sobreviviste al desierto.\n");
                resultado = GAME_OVER;
                break;
        }
    }

    system("pause");
    return resultado;

}
tNodoD* moverJugador(tNodoD *nodo, int pasos, char dir)
{
    int i=0,tope=0,restantes;
    if (!nodo)
    {
        printf("Error: jugador no inicializado.\n");
        return NULL;
    }

    ((tCasilla*)(nodo->dato))->tieneJ=0;

    while (i<pasos && !tope)
    {
        if (dir == 'A')
        {
            // chequeo si el siguiente es Inicio
            if (((tCasilla*)(nodo->sig->dato))->tipo == 'I')
            {
                // reboto
                restantes = pasos - i ;
                printf("Rebotaste en la Salida! Retrocedes %d casillero(s).\n", restantes);
                dir = 'R';
                pasos = restantes;
                i=0;
            }
            else
            {
               nodo = nodo->sig;
               i++;
            }

        }
        else
        {
            if (((tCasilla*)(nodo->ant->dato))->tipo == 'S')
            {
                // reboto: los pasos restantes van hacia adelante
                printf("Llegaste/estas en el Inicio! No podes retroceder mas.\n");
                tope = 1;
            }
            else
            {
                nodo = nodo->ant;
                i++;
            }

        }
    }

    ((tCasilla*)(nodo->dato))->tieneJ = 1;
    return nodo;
}

tNodoD* posicionarJugadorEnInicio(tListaD *l)
{
    tNodoD *act = *l;
    ((tCasilla*)(act->dato))->tieneJ = 1;
    return act;
}



void posicionarBandidosEnRuta(tBandido* bandidos,tListaD* ruta)
{
    tNodoD* actual = *ruta;

    if(!actual)
        return;


    do
    {
        if(((tCasilla*)(actual->dato))->tipo == 'B'){
            ((tCasilla*)(actual->dato))->tieneB = 1;
            ((tCasilla*)(actual->dato))->tipo = '.';
            bandidos->pos = actual;
            bandidos->activo = 1;
            bandidos++;
        }
        actual = actual->sig;
    } while(actual != *ruta);
}

void guardarMovimiento(tMovimiento* movimiento,tNodoD* nodo,char dir,int dado,char tipo)
{
    movimiento->tipoJugador = tipo;
    movimiento->pos = nodo;
    movimiento->pasos = dado;
    movimiento->direccion = dir;
}

void determinarMovimientosBandidos(tBandido* bandidos,int cantB,tNodoD* nodoJugador,tCola* colaMovimiento,int dado)
{
    int i;
    char dir;
    tMovimiento movimiento;

    for(i = 0; i < cantB; i++){
        if(bandidos->activo){
            calcularDistanciaMinima(bandidos->pos,nodoJugador,&dir);
            guardarMovimiento(&movimiento,bandidos->pos,dir,dado,'B');
            encolar(colaMovimiento,&movimiento,sizeof(tMovimiento));
        }
        bandidos++;
    }
}

void calcularDistanciaMinima(tNodoD* posB,tNodoD* posJ,char* dir)
{
    tNodoD* izq = posB, *der = posB;
    while(izq != posJ && der != posJ)
    {
        izq = izq->ant;
        der = der->sig;
    }

    if(izq == posJ)
        *dir = 'R';
    else
        *dir = 'A';
}

void moverBandidos(tBandido* bandidos,tMovimiento* movimiento,int cantB)
{
    tNodoD* actual = movimiento->pos;
    int i = 0;

    tBandido* bandidoEncontrado = buscarBandidoPorPosicion(bandidos, cantB, movimiento->pos);

    if (bandidoEncontrado != NULL)
    {

        if (((tCasilla*)(actual->dato))->tieneB > 0)
            ((tCasilla*)(actual->dato))->tieneB--;


        i = 0;

        if (movimiento->direccion == 'A')
        {
            while (i < movimiento->pasos)
            {
                actual = actual->sig;
                i++;
            }
        }
        else
        {
            while (i < movimiento->pasos)
            {
                actual = actual->ant;
                i++;
            }
        }

        bandidoEncontrado->pos = actual;
        ((tCasilla*)(actual->dato))->tieneB++;
    }

}

void eliminarBandido(tBandido* bandidos, int cantB, tNodoD* nodoColision)
{
    tBandido* bandidoEncontrado = buscarBandidoPorPosicion(bandidos, cantB, nodoColision);

    if (bandidoEncontrado != NULL)
        bandidoEncontrado->activo = 0;
}

tBandido* buscarBandidoPorPosicion(tBandido* bandidos, int cantB, tNodoD* posBuscada)
{
    int i = 0;
    tBandido* bandidoActual = bandidos;
    tBandido* bandidoEncontrado = NULL;

    while (i < cantB && bandidoEncontrado == NULL)
    {
        if (bandidoActual->pos == posBuscada && bandidoActual->activo)
            bandidoEncontrado = bandidoActual;
        else
        {
            bandidoActual++;
            i++;
        }
    }

    return bandidoEncontrado;
}

///----------------------------





int iniciarCaracteristicasJugador(tJugador *jugador,tConfig *conf)
{
    if(!jugador || !conf)
        return _ERROR;
    jugador->vidas = (int)conf->vidas_inicio;
    jugador->pierdeTurno = 0;
    jugador->protegido = 0;
    jugador->puntos = 0;
    return EXITO;
}

//
//int casoPruebaBIN(const char* archivo) ///ELIMINAR ESTA FUNCION ES SOLO DE PRUEBA
//{
//    tRegistroPartida partidas[10] = {
//        {1, 1, 150, 45},
//        {2, 2, 200, 80},
//        {1, 3, 120, 30},
//        {3, 4, 250, 30},
//        {4, 5, 20, 30},
//        {5, 6, 400, 80},
//        {1, 7, 400, 80},
//        {2, 8, 100, 10},
//        {3, 9, 100, 5},
//        {1, 10, 400, 80},
//    };
//    FILE *pf = fopen(archivo, "wb");
//
//    if (pf == NULL) {
//        perror("Error al abrir el archivo de prueba de carga de datos en arcivo bin");
//        return 1;
//    }
//
//    size_t escritos = fwrite(partidas, sizeof(tRegistroPartida), 10, pf);
//
//    if (escritos == 10) {
//        printf("Éxito: Se guardaron %zu registros correctamente.\n", escritos);
//    } else {
//        printf("Error: Solo se guardaron %zu registros.\n", escritos);
//    }
//
//    fclose(pf);
//    return 0;
//}

void mostrarRanking(const char* archivo) // le pasamos el archivo de partidas
{

    FILE* pf = fopen(archivo, "rb");
    if(!pf)
        return;

    tRegistroPartida partida;
    tLista lista;

    crearLista(&lista);

     fread(&partida, sizeof(tRegistroPartida), 1, pf);
    while(!feof(pf))
    {
        //inserta en una lista los registros del archivo de partidas, acumulando por jugador los puntos y movimientos
        insertarOrdenado(&lista, &partida, sizeof(tRegistroPartida), 0, acumularDuplicados, compararIDJugadores);
        fread(&partida, sizeof(tRegistroPartida), 1, pf);
    }


    printf("\n---JUGADOR--- ---PUNTAJE---\n");
    mostrarLista(&lista, mostrarPuntosJugadores);
    //deberiamos hacer una funcion si queremos gurdar el ranking en la estructura tRanking, por ahora solo se muestra por consola
    printf("\n---JUGADOR--- ---PUNTAJE---\n");
    mostrarTop(&lista,TOP);
    fclose(pf);
}

void mostrarTop(tLista *pLista,int top)
{
    ordenarLista(pLista,compararPuntosJugadores);

    // Mostramos por pantalla el encabezado
    printf("\n=============================================");
    printf("\n   TOP %d MEJORES PUNTAJES", top);
    printf("\n=============================================");
    printf("\n ID JUGADOR | PUNTAJE TOTAL | MOVIMIENTOS");
    printf("\n------------|---------------|-------------");


    tNodo* actual = *pLista;// para no perder referencia de pLista

    while(actual != NULL && top > 0)
    {
        tRegistroPartida* reg = (tRegistroPartida*)actual->dato; //casteo el void dato
         printf("\n %-10d | %-13d | %-11d",reg->id_jugador,reg->puntaje,reg->movimientos);
        top--;
        actual = actual->sig;
    }
    printf("\n=============================================\n");
}


void acumularDuplicados(void* datoLista, const void* datoAInsertar)
{
    tRegistroPartida* dI = (tRegistroPartida*)datoAInsertar;
    tRegistroPartida* dL = (tRegistroPartida*)datoLista;
    //acumulo puntaje
    dL->puntaje += dI->puntaje;
    //acumuo movimientos
    dL->movimientos += dI->movimientos;

}

int compararIDJugadores(const void* a, const void* b)
{
    tRegistroPartida* jug1 = (tRegistroPartida*)a;
    tRegistroPartida* jug2 = (tRegistroPartida*)b;

    return jug2->id_jugador - jug1->id_jugador;
}

int compararPuntosJugadores(const void* a, const void* b)
{
    tRegistroPartida* jug1 = (tRegistroPartida*)a;//tRanking* jug1 = (tRanking*)a;
    tRegistroPartida* jug2 = (tRegistroPartida*)b;//tRanking* jug2 = (tRanking*)b;

    return jug2->puntaje - jug1->puntaje;//return jug2->puntos - jug1->puntos;
}

void mostrarPuntosJugadores(const void* n)
{
    tRegistroPartida* jug = (tRegistroPartida*)n;
    printf("%d%-d\n", jug->id_jugador, jug->puntaje); ///MODIFICAR ESTO, SOLO LO PUSE ASI PARA QUE FUNCIONE
}


