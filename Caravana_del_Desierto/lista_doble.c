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


void recorrerListaDobleIzqADer(const tListaD* l, void accion(const void*,int))
{
    tNodoD* act = *l;
    tNodoD* ini = act;
    int num=1;

    if(!act)
        return;

    accion(act->dato,num);
    num++;
    act = act->sig;

    while(act != ini)
    {
        accion(act->dato,num);
        act = act->sig;
        num++;
    }
}

void vaciarListaD(tListaD* l)
{
    tNodoD* act = (*l);
    tNodoD* auxSig;

    if(!act)
        return;

    auxSig = act->sig;

    while(auxSig != (*l))
    {
        act = auxSig;
        auxSig = act->sig;

        free(act->dato);
        free(act);
    }
    free((*l)->dato);
    free(*l);

    *l = NULL;
}
