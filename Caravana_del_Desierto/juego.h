#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include "constantes.h"
#include "cola.h"
#include "config.h"
#include "lista.h"

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

typedef struct
{
    //char* nombre;
    int id_jugador;
    int puntos;
    int movimientos;
}tRanking; //este se utilizaría para el archivo de jugadores y para mostrar el ranking

typedef struct {
    int id_jugador;
    int id_partida;
    int puntaje;
    int movimientos;
} tRegistroPartida; //se ultiliza para gurdar el contenido del archivo binario "ARCH_PARTIDAS"


void menu(tConfig *c);
void mostrarRanking(const char* archivo);
int casoPruebaBIN(const char* archivo);
int compararPuntosJugadores(const void* a, const void* b);
void mostrarPuntosJugadores(const void* n);
int compararIDJugadores(const void* a, const void* b);
void acumularDuplicados(void* datoLista, const void* datoAInsertar);
void mostrarTop(tLista *pLista,int top);



void iniciarPartida(tConfig *c); //maquetado
//int juegoSigue();
int tirarDado();


#endif // JUEGO_H_INCLUDED
