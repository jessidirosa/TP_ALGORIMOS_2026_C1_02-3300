#include "juego.h"
#include "tablero.h"
#include "lista.h"

void menu(tConfig *c)
{
    unsigned opcion;

    printf("------CARAVANA DEL DESIERTO------\n\n");
    printf("Seleccione la opcion deseada:\n");
    printf("1 - Iniciar partida\n");
    printf("2 - Ver ranking\n");
    printf("3 - Salir\n");
    //4 - configurar partida

    scanf("%u", &opcion);
    while(opcion != 1 && opcion != 2 && opcion != 3)
    {
        printf("Ingrese una opcion valida: ");
        scanf("%u", &opcion);
    }

    switch (opcion)
    {
    case 1:
        system("cls");
        registrarJugador();
        iniciarPartida(c);
        break;

    case 2:
        system("cls");
        casoPruebaBIN(ARCH_PARTIDAS);///ELMINAR ESTE ARCHIVO, ES SOLO PARA PROBAR EL RANKING
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
    printf("\nBienvenido/a %s", nombreJugador);
}
void iniciarPartida(tConfig *c)
{
    //int dado;
    //tCola colaMovimiento;
    //tJugador jugador;
    //tTablero tablero;
    /*implementacion TXT*/



    // identificarJugador(); //funcion de jugador.h donde se hace la gestion de jugadores(no seria lo mismo que el jugador del juego)
    //inicializarJugador(&jugador); //inicializar la estructura del jugador.
    generarTablero_solucionTXT(c); //solucion en TXT antes de hacerlo con listas
    //generarTablero(); //funcion de tablero.h
    //posicionarJugadorEnInicio(&jugador,&tablero); //poner a jugador en I --> poner [I J]
    //crearBandidos(); //poner los bandidos al azar en el tablero segun config.max_bandidos
    //crearCola(&colaMovimiento);


    //while(juegoSigue(&jugador,&tablero))
    //{
        //if (jugador.pierdeTurno == 0)  //si el turno no esta perdido, juega el jugador
        //{
            //dado = tirarDado();
            //dir = elegirDireccion();
            //encolar(); //mov del jugador
            //registrarMovimiento(dado,dir);// en la cola/lista para mostrar al final de la partida
        //}

        //determinarMovimientoBandidos();
        //encolar(); //mov del bandido

        //determinarNuevoEstado();

        //mostrarTablero();
        //mostrarEstadoJugador();

    //}

    //finalizarPartida(); //determinar mensajes de ganó/perdiò
    //mostrarHistorial(); //mostrar los movimientos hechos durante la partida
    //guardarPartida(); // en partidas.dat

}

int tirarDado()
{
    return(rand() % 6 + 1);
}

/*int juegoSigue(tJugador* jugador) {
    return (jugador->vidas > 0 && jugador->posicion != salida);
}*/

int casoPruebaBIN(const char* archivo) ///ELIMINAR ESTA FUNCION ES SOLO DE PRUEBA
{
    tRegistroPartida partidas[10] = {
        {1, 1, 150, 45},
        {2, 2, 200, 80},
        {1, 3, 120, 30},
        {3, 4, 250, 30},
        {4, 5, 20, 30},
        {5, 6, 400, 80},
        {1, 7, 400, 80},
        {2, 8, 100, 10},
        {3, 9, 100, 5},
        {1, 10, 400, 80},
    };
    FILE *pf = fopen(archivo, "wb");

    if (pf == NULL) {
        perror("Error al abrir el archivo de prueba de carga de datos en arcivo bin");
        return 1;
    }

    size_t escritos = fwrite(partidas, sizeof(tRegistroPartida), 10, pf);

    if (escritos == 10) {
        printf("Éxito: Se guardaron %zu registros correctamente.\n", escritos);
    } else {
        printf("Error: Solo se guardaron %zu registros.\n", escritos);
    }

    fclose(pf);
    return 0;
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
        insertarOrdenado(&lista, &partida, sizeof(tRegistroPartida), 0, acumularDuplicados, compararIDJugadores);
        fread(&partida, sizeof(tRegistroPartida), 1, pf);
    }

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
/*
void mostrarPuntosJugadores(const void* n)
{
    tRanking* jug = (tRanking*)n;
    printf("%15s%-d\n", jug->nombre, jug->puntos);
}
*/
