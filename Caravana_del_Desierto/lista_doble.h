#ifndef LISTA_DOBLE_H_INCLUDED
#define LISTA_DOBLE_H_INCLUDED

typedef struct sNodoD
{
    void* dato;
    unsigned tam;
    struct sNodoD* ant;
    struct sNodoD* sig;

}tNodoD;

typedef tNodoD* tListaD;

void crearListaD(tListaD* l);
int insertarEnPosicRelListaD(tListaD* l, const void* dato, unsigned tam, int pos);
void recorrerListaDobleIzqADer(const tListaD* l, void accion(const void*));
int eliminarDeListaDobleOrd(tListaD* l, unsigned tam, void* dato, int cmp(const void*, const void*));
//void recorrerListaDobleDerAIzq(const tListaD* l, void accion(const void*));
int insertarEnPosicRelListaD(tListaD* l, const void* dato, unsigned tam, int pos);
int insertarAlInicioListaD(tListaD* l, const void* dato, unsigned tam);
int insertarAlFinalListaD(tListaD* l, const void* dato, unsigned tam);

#endif // LISTA_DOBLE_H_INCLUDED
