#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include "constantes.h"
#include "cola.h"
#include "config.h"
#include "lista.h"
<<<<<<< HEAD
=======

>>>>>>> 5f343b94048d3365f5e4886eda73024427a99785

/*typedef struct
{
    tNodo* pos;
    int vidas;
    int puntos;
    int protegido;
    int pierdeTurno;
} tJugador;*/

/*typedef struct
{
    tNodo* pos;
    int activo; // 1 = vivo, 0 = eliminado

} tBandido;*/

/*typedef struct
{
    void* tipoJugador;
    unsigned tamTipo;
    int pasos;
    int direccion;

} tMovimiento;*/
/*
typedef struct
{
    //char* nombre;
    int puntos;
    int movimientos;
}tRanking; //actualmente la logia funciona sin esta estructura*/

typedef struct {
    int id_jugador;
    int id_partida;
    int puntaje;
    int movimientos;
} tRegistroPartida; //se ultiliza para gurdar el contenido del archivo binario "ARCH_PARTIDAS" y mostrar el ranking


void menu(tConfig *c);
void registrarJugador();
void mostrarRanking(const char* archivo);
int casoPruebaBIN(const char* archivo);
int compararPuntosJugadores(const void* a, const void* b);
void mostrarPuntosJugadores(const void* n);
int compararIDJugadores(const void* a, const void* b);
void acumularDuplicados(void* datoLista, const void* datoAInsertar);
void mostrarTop(tLista *pLista,int top);
int ingresar(unsigned tam);
int opcionValida(unsigned opcion);
void ejecutarOpcion(unsigned opcion,tConfig* c);


void iniciarPartida(tConfig *c); //maquetado
//int juegoSigue();
int tirarDado();


#endif // JUEGO_H_INCLUDED
