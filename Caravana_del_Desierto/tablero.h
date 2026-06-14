#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED
#include "config.h"
#include "lista_doble.h"

typedef struct {
    char tipo;    // 'I', 'S', '.', 'B', 'O', 'P', 'V', 'T'
    int  tieneJ;  // 0 = no hay jugador, 1 = jugador acá
    int tieneB; //0 no, 1 si
} tCasilla;

int generarTablero(tConfig* c, tListaD* l);
void mostrarTablero(const void* l,int num);
int cargarArchCaravana(const char* nombreArch, tListaD* l);


#endif // TABLERO_H_INCLUDED
