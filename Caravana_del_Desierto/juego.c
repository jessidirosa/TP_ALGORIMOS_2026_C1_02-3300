#include "juego.h"

void menu()
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
//        iniciarPartida();
        break;

    case 2:
        system("cls");
//        verRanking();
        break;

    case 3:
        break;
    }
}

void iniciarPartida()
{
    int dado;
    //tCola colaMovimiento;
    //tJugador jugador;
    //tTablero tablero;


    // identificarJugador(); //funcion de jugador.h donde se hace la gestion de jugadores(no seria lo mismo que el jugador del juego)
    //inicializarJugador(&jugador); //inicializar la estructura del jugador.
    //generarTablero(); //funcion de tablero.h
    //posicionarJugadorEnInicio(&jugador,&tablero); //poner a jugador en I --> poner [I J]
    //crearBandidos(); //poner los bandidos al azar en el tablero segun config.max_bandidos
    //crearCola(&colaMovimiento);


    //while(juegoSigue(&jugador,&tablero))
    //{
        //if (jugador.pierdeTurno == 0)  //si el turno no esta perdido, juega el jugador
        //{
            dado = tirarDado();
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
