#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include "constantes.h"
#include "cola.h"
#include "config.h"

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
    char* nombre;
    int puntos;

}tRanking; //este se utilizaría para el archivo de jugadores y para mostrar el ranking


void menu(tConfig *c);
void mostrarRanking(const char* archivo);


void iniciarPartida(tConfig *c); //maquetado
//int juegoSigue();
int tirarDado();


#endif // JUEGO_H_INCLUDED
