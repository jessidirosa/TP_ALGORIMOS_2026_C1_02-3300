#ifndef LISTA_DOBLE_H_INCLUDED
#define LISTA_DOBLE_H_INCLUDED

typedef struct sNodoD
{
    void* dato;
    unsigned tam;
    struct sNodo* ant;
    struct sNodo* sig;

}tNodoD;

typedef tNodoD* tListaD;

void crearLista(tLista* l);
int insertarEnPosicRelListaD(tLista* l, const void* dato, unsigned tam, int pos);
void recorrerListaDobleIzqADer(const tLista* l, void accion(const void*));
int eliminarDeListaDobleOrd(tLista* l, unsigned tam, void* dato, int cmp(const void*, const void*));
void recorrerListaDobleDerAIzq(const tLista* l, void accion(const void*));



#endif // LISTA_DOBLE_H_INCLUDED
