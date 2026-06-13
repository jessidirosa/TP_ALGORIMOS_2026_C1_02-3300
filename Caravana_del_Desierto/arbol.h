#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include "constantes.h"

typedef struct sNodoA
{
    void* dato;
    unsigned tam;
    struct sNodoA* izq;
    struct sNodoA* der;

}tNodoA;

typedef tNodoA* tArbol;

typedef struct
{
    char alias[MAX_ALIAS];

}tClave;

typedef struct
{
    tClave clave;
    int pos;

}tIndice;

typedef struct {

    int id;
    char nombre[MAX_NOMBRE];
    char alias[MAX_BUF];
} tArchJug;

void destruirArbol(tArbol* a);
int ponerEnArbol(tArbol* a, void* dato, unsigned tam, int cmp(const void*, const void*));
void crearArbol(tArbol* arbol);
int compararEnteros(const void* a, const void* b);
int indexarArchivoDesordenadoJugadores(tArbol* arbol, const char* nombreArch);
int cargarArchivoIndiceJugadores(tArbol* arbol, const char* archIdx);
void cargarArbolAArchivoIndiceOrdenado(const tArbol* arbol, tIndice* idx, FILE* pf);
int cargarArchIndiceAArbolBalanceado(tArbol* arbol, const char* nombreArch);
int insertarIdxEnArbolBalanceado(tArbol* arbol, FILE* pf, int inicio, int fin);
void cargarArbolAArchivoIndicePreorden(const tArbol* arbol, tIndice* idx, FILE* pf);
void recorrerPreorden(const tArbol* arbol, void accion(void*));
void recorrerInorden(const tArbol* arbol, void accion(void*));
int indiceArchivoJugadores(tArbol* arbol, const char* archJug, const char* archIdx);
int buscarEnIndice(tArbol* idx, const char* aliasJugador, tIndice* dato, int cmp(const void*, const void*));



int compararIdx(const void* clave1, const void* clave2);
int compararClave(const void* alias, const void* idx);

#endif // ARBOL_H_INCLUDED
