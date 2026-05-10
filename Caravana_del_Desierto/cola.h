#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TODO_OK 1
#define COLA_LLENA 2
#define COLA_VACIA 3
#define COLA_NOLLENA 4
#define COLA_NOVACIA 5
#define SIN_MEM 0
#define MIN(a,b) (a < b ? a : b)


typedef struct sNodo
{
    void * dato;
    unsigned tam;
    struct sNodo *sig;
} tNodo;

typedef struct
{
    tNodo* pri;
    tNodo* ult;
} tCola;



void crearCola(tCola* c);
int colaLlena(const tCola* c, unsigned cantBytes);
int colaVacia(const tCola* c);
void vaciarCola(tCola* c);
int encolar(tCola* c,const void* d, unsigned cantBytes);
int desencolar(tCola* c, void* d, unsigned cantBytes);
int verTope(tCola* c, void* d, unsigned cantbytes);
#endif // COLA_H_INCLUDED
