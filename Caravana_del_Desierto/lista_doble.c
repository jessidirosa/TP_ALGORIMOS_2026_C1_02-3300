#include "lista_doble.h"
#include "constantes.h"

void crearListaD(tListaD* l)
{
    *l = NULL;
}

int insertarEnPosicRelListaD(tListaD* l, const void* dato, unsigned tam, int pos)
{
    tNodoD* pAct = *l;
    tNodoD* auxAnt;
    int i;
    tNodoD* nue = malloc(sizeof(tNodoD));
    if(!nue)
        return SIN_MEM;

    nue->dato = malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return SIN_MEM;
    }

    memcpy(nue->dato, dato, tam);
    nue->tam = tam;

    if(!pAct)
    {
        (*l) = nue;
        auxAnt = (*l);
        nue->ant = (*l);
        nue->sig = (*l);
        return TODO_OK;
    }

    auxAnt = pAct->ant;

    for(i=0; i<pos; i++)
        pAct = pAct->sig;

    auxAnt = pAct->ant;

    auxAnt->sig = nue;
    pAct->ant = nue;

    nue->ant = auxAnt;
    nue->sig = pAct;

    return TODO_OK;
}

int insertarAlInicioListaD(tListaD* l, const void* dato, unsigned tam)
{
    tNodoD* pAct = *l;
    tNodoD* auxAnt;
    tNodoD* nue = malloc(sizeof(tNodoD));
    if(!nue)
        return SIN_MEM;

    nue->dato = malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return SIN_MEM;
    }

    memcpy(nue->dato, dato, tam);
    nue->tam = tam;

    if(!pAct)
    {
        (*l) = nue;
        auxAnt = (*l);
        nue->ant = (*l);
        nue->sig = (*l);
        return TODO_OK;
    }

    auxAnt = pAct->ant;

    auxAnt->sig = nue;
    pAct->ant = nue;

    nue->ant = auxAnt;
    nue->sig = pAct;
    (*l) = nue;

    return TODO_OK;

}

int insertarAlFinalListaD(tListaD* l, const void* dato, unsigned tam)
{
    tNodoD* pAct = *l;
    tNodoD* auxAnt;
    tNodoD* nue = malloc(sizeof(tNodoD));
    if(!nue)
        return SIN_MEM;

    nue->dato = malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return SIN_MEM;
    }

    memcpy(nue->dato, dato, tam);
    nue->tam = tam;

    if(!pAct)
    {
        (*l) = nue;
        auxAnt = (*l);
        nue->ant = (*l);
        nue->sig = (*l);
        return TODO_OK;
    }

    auxAnt = pAct->ant;

    auxAnt->sig = nue;
    pAct->ant = nue;

    nue->ant = auxAnt;
    nue->sig = pAct;

    return TODO_OK;

}



void recorrerListaDobleDerAIzq(const tListaD* l, void accion(const void*))
{
   tNodoD* act = *l;
    tNodoD* ini = act;

    accion(act->dato);
    act = act->ant;

    while(act != ini)
    {
        accion(act->dato);
        act = act->ant;
    }
}

void recorrerListaDobleIzqADer(const tListaD* l, void accion(const void*))
{
    tNodoD* act = *l;
    tNodoD* ini = act;

    accion(act->dato);
    act = act->sig;

    while(act != ini)
    {
        accion(act->dato);
        act = act->sig;
    }
}

int eliminarDeListaDobleOrd(tListaD* l, unsigned tam, void* dato, int cmp(const void*, const void*))
{
    tNodoD* act = *l;
    tNodoD* auxAnt, *auxSig;

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
