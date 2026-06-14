#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include "cola.h"
#include "constantes.h"
#define ERR_MALLOC -1
#define EXITO 0
#define LISTA_VACIA 10
#define POS_INVALIDA -2
#define DUPLICADO 3

typedef tNodo* tLista;
void crearLista(tLista *lista);
int ordenarLista(tLista* pl, int cmp(const void*, const void*));
int insertarOrdenado(tLista* pl, const void* dato, unsigned tam, int sinDup, void accion(void*, const void*), int cmp(const void*, const void*));
void mostrarLista(tLista* l, void accion(const void* dato));
void vaciarLista(tLista* lista);
#endif // LISTA_H_INCLUDED
