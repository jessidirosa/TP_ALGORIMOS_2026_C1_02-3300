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
int insertarPrincipioLista(tLista *plista, const void* dato, unsigned tamDato);
int verPrincipioLista(const tLista *plista, void* dato, unsigned tamDato);
int sacarPrincipioLista(tLista *plista, void* dato, unsigned tamDato);
int insertarFinalLista(tLista *plista,const void* dato, unsigned tamDato);
int sacarFinalpioLista(tLista *plista,void* dato,unsigned tamDato);
int verFinalLista(const tLista *plista, void* dato, unsigned tamDato);
int insertarPosicionLista(tLista *lista, const void* dato, unsigned tamDato, unsigned pos);
int sacarPosicionLista(tLista *plista, void* dato, unsigned tamDato, unsigned pos);
int verPosicionLista(const tLista *plista, void* dato, unsigned tamDato, unsigned pos);
void recorrerLista( tLista *pLista, void accion(void*, void*), void *param);
int ordenarLista(tLista* pl, int cmp(const void*, const void*));
int insertarOrdenado(tLista* pl, const void* dato, unsigned tam, int sinDup, void accion(void*, const void*), int cmp(const void*, const void*));
void mostrarLista(tLista* l, void accion(const void* dato));

#endif // LISTA_H_INCLUDED
