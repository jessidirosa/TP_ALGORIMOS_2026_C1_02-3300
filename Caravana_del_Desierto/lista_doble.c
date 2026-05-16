#include "lista_doble.h"
#include "constantes.h"

void crearLista(tLista* l)
{
    *l = NULL;
}

int insertarEnPosicRelListaD(tLista* l, const void* dato, unsigned tam, int pos)
{
    tNodoD* pAct = *l;
    tNodoD* auxAnt, * auxSig;


}


void recorrerListaDobleDerAIzq(const tLista* l, void accion(const void*))
{
    tNodo* act = *l;

    while(act && act->sig)
        act = act->sig;

    while(act)
    {
        accion(act->dato);
        act = act->ant;
    }
}

void recorrerListaDobleIzqADer(const tLista* l, void accion(const void*))
{
    tNodo* act = *l;

    while(act && act->ant)
        act = act->ant;

    while(act)
    {
        accion(act->dato);
        act = act->sig;
    }
}

int eliminarDeListaDobleOrd(tLista* l, unsigned tam, void* dato, int cmp(const void*, const void*))
{
    tNodo* act = *l;
    tNodo* auxAnt, *auxSig;

    while(cmp(dato, act->dato) > 0 && act->sig)
        act = act->sig;

    while(cmp(dato, act->dato) < 0 && act->ant)
        act = act->ant;

    if(act && cmp(dato, act->dato))
        return NO_ENCONTRADO;

    auxAnt = act->ant;
    auxSig = act->sig;

    if(auxSig)
        auxSig->ant = auxAnt;

    if(auxAnt)
        auxAnt->sig = auxSig;

    if(auxSig)
        (*l) = auxSig;
    else
        (*l) = auxAnt;

    memcpy(dato, act->dato, tam);

    free(act->dato);
    free(act);

    return TODO_OK;
}
