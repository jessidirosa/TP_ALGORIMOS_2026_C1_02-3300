#include "juego.h"
#include "tablero.h"
#include "lista.h"
#include "animacion.h"


//----------Manejo del MENU----------
void menu(tConfig *c, tArbol* idx)
{
    unsigned opcion;

    do
    {
        printf("+======================================================+\n");
        printf("|              CARAVANA DEL DESIERTO                   |\n");
        printf("+======================================================+\n");
        printf("|Seleccione la opcion deseada:                         |\n");
        printf("|1 - Iniciar partida                                   |\n");
        printf("|2 - Ver ranking                                       |\n");
        printf("|3 - Salir                                             |\n");
        printf("+======================================================+\n");
        //4 - configurar partida (lo agregamos al menu y solicitamos una "contraseña", la comparamos con la de la funcion y accedemos al menu de config para cargar el archivo config.txt

        opcion = ingresar(TAM_OP);

        while(!opcionValida(opcion))
        {
            printf("Ingrese una opcion valida: ");
            opcion = ingresar(TAM_OP);
        }

        ejecutarOpcion(opcion, c, idx);

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

void ejecutarOpcion(unsigned opcion,tConfig* c, tArbol* idx)
{
    char alias[MAX_BUF];
    switch (opcion)
    {
    case 1:
        system("cls");
        registrarJugador(idx, alias);
        iniciarPartida(c, alias);
        break;

    case 2:
        system("cls");
        mostrarRanking(ARCH_PARTIDAS);
        break;

    case 3:
        break;
    }
}

//------------REGISTRO DE USUARIO--------------

void registrarJugador(tArbol* idx, char* aliasJugador)
{
    printf("\nIngrese su alias (distingue mayusculas de minusculas): ");
    scanf(" %[^\n]",aliasJugador); // [^\n] permite leer espacios hasta presionar Enter y El espacio antes de % es limpia cualquier '\n' pendiente en el buffer
    identificarJugador(aliasJugador, idx); //funcion de jugador.h donde se hace la gestion de jugadores(no seria lo mismo que el jugador del juego)
}

void identificarJugador(const char* aliasJugador, tArbol* idx)
{
    tIndice jugador;
    tArchJug datosJugador;

    if(!buscarEnIndice(idx, aliasJugador, &jugador, compararClave)) //buscamos por clave alias en el arbol, y lo traemos en jugador
        altaJugador(idx, aliasJugador, ARCH_JUGADORES); //vemos cantReg para el id, pedimos el nombre y cargamos en idx y en archivo
    else
    {
        buscarEnArchivo(&jugador, ARCH_JUGADORES, &datosJugador); //buscamos el jugador por indice en el archivo, y traemos todo el registro en datosJugador
        mostrarDatosYValidar(&datosJugador, idx); //¿es usted? S | N
    }
}

void buscarEnArchivo(tIndice* jugador, const char* archJug, tArchJug* datosJugador)
{
    FILE* pf = fopen(archJug, "rb");
    if(!pf)
        return;

    fseek(pf, jugador->pos * sizeof(tArchJug), SEEK_SET);
    fread(datosJugador, sizeof(tArchJug), 1, pf);

    fclose(pf);
}

void mostrarDatosYValidar(tArchJug* datosJugador, tArbol* idx)
{
    char opcion;

    printf("Este alias ya esta en uso. Es usted?\n");
    printf("ID: %d\nNombre: %s\nAlias: %s\n\n", datosJugador->id, datosJugador->nombre, datosJugador->alias);
    printf("Presione 'S' si es correcto, o 'N' si no lo es, para cargar nuevamente el alias:\n");

    while ((getchar()) != '\n');
    scanf("%c", &opcion);

    while(toupper(opcion) != 'S' && toupper(opcion) != 'N')
    {
        printf("Opcion invalida\n");
        printf("Presione 'S' si es correcto, o 'N' si no lo es, para cargar nuevamente el alias:\n");
        scanf("%c", &opcion);
    }

    if(toupper(opcion) == 'N')
        registrarJugador(idx, datosJugador->alias);

    printf("\nBienvenido/a %s\nIniciando partida...", datosJugador->alias);
    return;

}

void altaJugador(tArbol* idx, const char* alias, const char* archJug)
{
    tArchJug jugador;
    tIndice i;
    FILE* pf = fopen(archJug, "ab");
    if(!pf)
        return;

    printf("Ingrese su nombre completo: ");
    scanf(" %[^\n]", jugador.nombre);
    fseek(pf, 0L, SEEK_END);
    jugador.id = (ftell(pf) / sizeof(tArchJug)) + 1;
    strcpy(jugador.alias, alias);

    strcpy(i.clave.alias, alias);
    i.pos = (ftell(pf) / sizeof(tArchJug));

    fwrite(&jugador, sizeof(tArchJug), 1, pf);
    ponerEnArbol(idx, &i, sizeof(tIndice), compararIdx);

    fclose(pf);

    printf("\n\nRegistrado correctamente\n");
    system("pause");
}

/// ////////////////INICIAR PARTIDA///////////// ///

void iniciarPartida(tConfig *c, const char* alias)
{
    tCola colaMovimiento, historialMov;
    tJugador jugador;
    tMovimiento movimiento;
    tListaD ruta;
    tNodoD *nodoJugador = NULL, *nodoCampamento;
    int dado,game_over = 1,turno =1, salir = 0;
    char dir;
    tBandido bandidos[c->maximo_bandidos];

    iniciarCaracteristicasJugador(&jugador,c);

    crearListaD(&ruta);
    crearCola(&colaMovimiento);
    crearCola(&historialMov);

    if(!generarTablero(c, &ruta))
        printf("no se pudo generar el tablero\n");


    posicionarBandidosEnRuta(bandidos,&ruta); //guarda la direccion de cada bandido en la ruta

    nodoJugador = posicionarJugadorEnInicio(&ruta); //poner a jugador en I --> poner [I J]
    nodoCampamento = nodoJugador;

    while(jugador.vidas != 0 && game_over && !salir) /// esta invertida la logica del game_over
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
        printf("Presione X para salir del juego\n\n");

        if(jugador.pierdeTurno)
        {
            printf("Perdes este turno por la Tormenta de Arena!\n");
            jugador.pierdeTurno = 0;
            system("cls");
            printf("+===========================================================+\n");
            printf("|          CARAVANA DEL DESIERTO  ~  Resultado Dia %-2d      |\n", turno);
            printf("+===========================================================+\n\n");
            jugador.puntos -= 2;
            escena_perdida_turno(jugador.puntos);
            turno++;
            system("pause");
            system("cls");
        }
        else
        {
            //primero movemos bandidos
            printf("+===========================================================+\n");
            printf("|          Los bandidos estan calculando sus pasos...       |\n");
            printf("+===========================================================+\n\n");
            printf("Cuidado, se estan moviendo a distintas velocidades para atraparte!\n");
            system("pause");

            determinarMovimientosBandidos(bandidos, c->maximo_bandidos, nodoJugador, &colaMovimiento);
            while(colaVacia(&colaMovimiento) == COLA_NOVACIA)
            {
                desencolar(&colaMovimiento,&movimiento,sizeof(tMovimiento));
                moverBandidos(bandidos,&movimiento, c->maximo_bandidos);
            }

            //mostramos el tablero actualizado para que el jugador decida
            system("cls");
            printf("+===========================================================+\n");
            printf("|        Posiciones tras el movimiento de los bandidos:     |\n");
            printf("+===========================================================+\n\n");
            recorrerListaDobleIzqADer(&ruta, mostrarTablero);
            printf("\n\n");

            //turno del jugador
            dado = tirarDado();
            printf("+===========================================================+\n");
            printf("|                  Tiraste el dado:          %d              |\n", dado);
            printf("+===========================================================+\n\n");
            if(calcularDistanciaAlInicio(nodoJugador) >= dado)
            {
                printf("Hacia donde queres moverte? (A = Avanzar / R = Retroceder / X = Salir: ");
                scanf(" %c", &dir);
                dir = toupper(dir);
                while(dir != 'A' && dir != 'R' && dir != 'X')
                {
                    printf("Direccion invalida. Ingresa A o R (o X para salir): ");
                    scanf(" %c", &dir);
                    dir = toupper(dir);
                }
            }
            else
            {
                printf("Solo puedes avanzar. Ingresa A (A = Avanzar) o X (X = Salir): ");
                scanf(" %c", &dir);
                dir = toupper(dir);
                while(dir != 'A' && dir != 'X')
                {
                    printf("Direccion invalida. Ingresa A (o X para salir): ");
                    scanf(" %c", &dir);
                    dir = toupper(dir);
                }
            }

            if(dir == 'X')
            {
                ///funcion de vaciar y destruir
                salir = 1;
            }

            if(!salir)
            {
                //movemos al jugador
                guardarMovimiento(&movimiento,nodoJugador,dir,dado,'J');
                encolar(&colaMovimiento,&movimiento,sizeof(tMovimiento));

                while(colaVacia(&colaMovimiento) == COLA_NOVACIA)
                {
                    desencolar(&colaMovimiento,&movimiento,sizeof(tMovimiento));
                    nodoJugador = moverJugador(nodoJugador, movimiento.pasos, movimiento.direccion);
                    registrarMovimientoEnHistorial(&historialMov,movimiento.pasos,movimiento.direccion);
                }

                // 3. RESULTADOS DEL DÍA
                system("cls");
                printf("+===========================================================+\n");
                printf("|          CARAVANA DEL DESIERTO  ~  Resultado Dia %-2d       |\n", turno);
                printf("+===========================================================+\n\n");

                // Mostrar cómo quedó todo tras tu movimiento antes de analizar
                recorrerListaDobleIzqADer(&ruta, mostrarTablero);
                printf("\n\n");

                if(analizarJuego(nodoJugador, &jugador, nodoCampamento, &nodoJugador,bandidos, c->maximo_bandidos) == GAME_OVER)
                    game_over = 0;
                if(jugador.protegido > 0)
                    jugador.protegido--;

                turno++;
            }
        }
    }

    system("cls");

    if(salir)
    {
        printf("Saliendo... La partida no se guardara\n\n");
        return;
    }

    if(jugador.vidas == 0)
        printf("Perdiste! \nPuntos finales: %d\n\n", jugador.puntos);
    else
    {
        printf("=== VICTORIA! ===\n");
        printf("Puntos conseguidos: %d | Vidas sobrantes: %d\n", jugador.puntos, jugador.vidas);
    }

    guardarPartida(alias, jugador.puntos, mostrarHistorialMovimientos(&historialMov)); // en partidas.dat
    vaciarListaD(&ruta);
}

int guardarPartida(const char* alias, int puntos, int cantMov)
{
    tRegistroPartida partida;
    FILE* pf = fopen(ARCH_PARTIDAS, "ab");
    if(!pf)
        return ERR_ARCH;

    strcpy(partida.alias, alias);
    fseek(pf, 0L, SEEK_END);
    partida.id_partida = (ftell(pf) / sizeof(tRegistroPartida)) + 1;
    partida.movimientos = cantMov;
    partida.puntaje = puntos;

    fwrite(&partida, sizeof(tRegistroPartida), 1, pf);

    fclose(pf);
    return TODO_OK;
}

int tirarDado()
{
    return(rand() % 6 + 1);
}

int analizarJuego(tNodoD *nodo, tJugador *jugador, tNodoD *nodoInicio,tNodoD** nodoJugador,tBandido* bandidos, int cantB)
{
    tCasilla *cas = (tCasilla*)nodo->dato;
    int resultado = EXITO;
    int puntosRand;
    int oasisUsado = 0;

    if (cas->tieneB > 0)
    {
        if (cas->tipo == 'O' && cas->tieneB == 1)
        {
            escena_defensa_oasis();
            cas->tieneB--;
            eliminarBandido(bandidos, cantB, nodo);
            oasisUsado = 1;
        }
        else
        {
            if (jugador->protegido && cas->tipo != 'T')
            {
                jugador->protegido = 0; // Se consume el escudo
                cas->tieneB--;
                eliminarBandido(bandidos, cantB, nodo);
                escena_defensa_oasis();
                system("pause");
            }
            if (cas->tieneB > 0) //si hay otro badnido en la casilla,MUERO
            {
                jugador->vidas--;
                if (jugador->vidas == 0)
                {

                    escena_game_over();
                    jugador->puntos++;
                    system("pause");
                    return GAME_OVER;
                }
                else
                {

                    cas->tieneJ = 0;
                    cas->tieneB--;
                    eliminarBandido(bandidos, cantB, nodo);

                    ((tCasilla*)nodoInicio->dato)->tieneJ = 1;
                    *nodoJugador = nodoInicio;

                    escena_bandido(jugador->vidas);
                    system("pause");
                    return EXITO;
                }

            }
        }
    }

    // Solo si sobrevivio y sigue en la casilla
    switch (cas->tipo)
    {
    case '.':
        escena_dia_normal();
        break;
    case 'P':
        puntosRand = rand() % 5 + 1;
        jugador->puntos += puntosRand; // puntos aleatorios del 1 al 5
        escena_premio(puntosRand);
        cas->tipo = '.';
        break;
    case 'V':
        jugador->vidas++;
        escena_vida_extra();
        cas->tipo = '.';
        break;
    case 'O':
        if(!oasisUsado)
        {
            jugador->protegido = 2;
            escena_oasis();
        }
        break;
    case 'T':
        if (jugador->protegido)
        {
            escena_tormenta_protegido();
            jugador->protegido = 0;
        }
        else
        {
            jugador->pierdeTurno = 1;
            escena_tormenta();
        }
        break;
    case 'S':
        escena_victoria(PUNTOS_GANADOR);
        jugador->puntos += PUNTOS_GANADOR;
        resultado = GAME_OVER;
        break;
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
            nodo = nodo->ant;
            i++;
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
        if(((tCasilla*)(actual->dato))->tipo == 'B')
        {
            ((tCasilla*)(actual->dato))->tieneB = 1;
            ((tCasilla*)(actual->dato))->tipo = '.';
            bandidos->pos = actual;
            bandidos->activo = 1;
            bandidos++;
        }
        actual = actual->sig;
    }
    while(actual != *ruta);
}

void guardarMovimiento(tMovimiento* movimiento,tNodoD* nodo,char dir,int dado,char tipo)
{
    movimiento->tipoJugador = tipo;
    movimiento->pos = nodo;
    movimiento->pasos = dado;
    movimiento->direccion = dir;
}

void determinarMovimientosBandidos(tBandido* bandidos, int cantB, tNodoD* nodoJugador, tCola* colaMovimiento)
{
    int i, pasosAleatorios;
    char dir;
    tMovimiento movimiento;

    for(i = 0; i < cantB; i++)
    {
        if(bandidos->activo)
        {
            calcularDistanciaMinima(bandidos->pos, nodoJugador, &dir);
            pasosAleatorios = (rand() % 3) + 1; //movimientos aleatorios por cada bandido
            guardarMovimiento(&movimiento, bandidos->pos, dir, pasosAleatorios, 'B');
            encolar(colaMovimiento, &movimiento, sizeof(tMovimiento));
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

void moverBandidos(tBandido* bandidos, tMovimiento* movimiento, int cantB)
{
    tNodoD* actual = movimiento->pos;
    int i = 0;

    tBandido* bandidoEncontrado = buscarBandidoPorPosicion(bandidos, cantB, movimiento->pos);

    if (bandidoEncontrado != NULL)
    {
        if (((tCasilla*)(actual->dato))->tieneB > 0)
            ((tCasilla*)(actual->dato))->tieneB--;

        i = 0;

        if (movimiento->direccion == 'A') // El bandido avanza
        {
            while (i < movimiento->pasos)
            {
                // para que los bandidos no se muevan al final ni a la casilla que esta el jugador
                if (actual->sig == NULL || actual->sig->sig == NULL || ((tCasilla*)(actual->sig->dato))->tieneJ == 1) /// VER!
                {
                    break;
                }
                actual = actual->sig;
                i++;
            }
        }
        else
        {
            while (i < movimiento->pasos)
            {
                // para que los bandidos no se muevan al inicio ni a la casilla que esta el jugador
                if (actual->ant == NULL || actual->ant->ant == NULL || ((tCasilla*)(actual->ant->dato))->tieneJ == 1)
                {
                    break;
                }
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

int calcularDistanciaAlInicio(tNodoD *nodoJugador)
{
    int distancia = 0;
    tNodoD *actual = nodoJugador;


    while (actual != NULL && ((tCasilla*)(actual->dato))->tipo != 'I')
    {
        distancia++;
        actual = actual->ant;
    }

    return distancia;
}
///----------------------------

void registrarMovimientoEnHistorial(tCola* historialMov, int pasos, char direccion)
{
    char hmov[5];
    char dirFormateada;

    if (direccion == 'A')
        dirFormateada = 'F';
    else
        dirFormateada = 'B';

    sprintf(hmov, "%c%d", dirFormateada, pasos);

    encolar(historialMov, hmov, sizeof(hmov));
}

int mostrarHistorialMovimientos(tCola* historialMov)
{
    char hmov[5];
    int i = 1, cantMov = 0;
    printf("+===========================================================+\n");
    printf("|            Historial de movimientos del Jugador            |\n");
    printf("+===========================================================+\n\n");
    while(colaVacia(historialMov) == COLA_NOVACIA)
    {
        desencolar(historialMov,hmov,sizeof(hmov));
        printf("%.2d: %s\n",i,hmov);
        cantMov += atoi(hmov + 1); //para guardar en partidas.dat
        i++;
    }

    return cantMov;
}


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
        insertarOrdenado(&lista, &partida, sizeof(tRegistroPartida), 0, acumularDuplicados, compararAlias);
        fread(&partida, sizeof(tRegistroPartida), 1, pf);
    }


    printf("\n---JUGADOR---\t---PUNTAJE---\n");
    mostrarLista(&lista, mostrarPuntosJugadores);

    mostrarTop(&lista,TOP);
    fclose(pf);
    vaciarLista(&lista);
}

int compararAlias(const void* s1, const void* s2)
{
    char* alias1 = (char*)s1;
    char* alias2 = (char*)s2;

    return strcmp(alias1, alias2);
}

void mostrarTop(tLista *pLista, int top)
{
    tRegistroPartida* reg;
    ordenarLista(pLista,compararPuntosJugadores);

    // Mostramos por pantalla el encabezado
    printf("\n=================================");
    printf("\n   TOP %d MEJORES PUNTAJES", top);
    printf("\n=================================");
    printf("\n ALIAS JUGADOR | PUNTAJE TOTAL ");
    printf("\n---------------|---------------");


    tNodo* actual = *pLista;// para no perder referencia de pLista

    while(actual != NULL && top > 0)
    {
        reg = (tRegistroPartida*)actual->dato; //casteo el void dato
        printf("\n %-10s    | %-13d",reg->alias,reg->puntaje);
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

int compararPuntosJugadores(const void* a, const void* b)
{
    tRegistroPartida* jug1 = (tRegistroPartida*)a;//tRanking* jug1 = (tRanking*)a;
    tRegistroPartida* jug2 = (tRegistroPartida*)b;//tRanking* jug2 = (tRanking*)b;

    return jug2->puntaje - jug1->puntaje;//return jug2->puntos - jug1->puntos;
}

void mostrarPuntosJugadores(const void* n)
{
    tRegistroPartida* jug = (tRegistroPartida*)n;
    printf("%s\t\t\t%-d\n", jug->alias, jug->puntaje);
}
