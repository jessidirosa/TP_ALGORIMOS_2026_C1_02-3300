#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED
#include "config.h"
#include "lista_doble.h"

//void generarTablero();
//crearTablero();
//distribuirElementos();
//int tableroTieneSolucion();
// int guardarTablero(); //en caravana.txt

/*generar tablero solucion facil y tempotal TXT*/
void colocarElemAleatorios_solucionTXT(char tablero[], int n, char elemento, int cantidad);
int guardarTablero_solucionTXT(char tablero[], int n);
void generarTablero_solucionTXT(tConfig *c);
int mostrarTablero_solucionTXT();


#endif // TABLERO_H_INCLUDED
