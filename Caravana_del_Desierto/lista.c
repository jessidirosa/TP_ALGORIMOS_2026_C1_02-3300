#include "lista.h"
void crearLista(tLista *plista)
{
    *plista = NULL;
}

int insertarPrincipioLista(tLista *plista, const void* dato, unsigned tamDato)
{
    tNodo *nue;
    if (!(nue = (tNodo*)malloc(sizeof(tNodo))))
        return ERR_MALLOC;
    if(!(nue->dato = malloc(tamDato)))
    {
        free(nue);
        return ERR_MALLOC;
    }
    memcpy(nue->dato,dato,tamDato);
    nue->tam = tamDato;
    nue->sig = *plista;

    *plista = nue;
    return EXITO;
}

int verPrincipioLista(const tLista *plista, void* dato, unsigned tamDato)
{
    if(!*plista)
        return LISTA_VACIA;
    memcpy(dato,(*plista)->dato,MIN((*plista)->tam,tamDato));
    return EXITO;
}

int sacarPrincipioLista(tLista *plista, void* dato, unsigned tamDato)
{
    tNodo *elim = *plista;
    if(!*plista)
        return LISTA_VACIA;
    *plista = elim->sig;
    memcpy(dato,elim->dato,MIN(elim->tam,tamDato));
    free(elim->dato);
    free(elim);
    return EXITO;

}
int insertarFinalLista(tLista *plista,const void* dato, unsigned tamDato)
{
    tNodo *nue;
    while(*plista)
        plista = &(*plista)->sig;

    if (!(nue = (tNodo*)malloc(sizeof(tNodo))))
        return ERR_MALLOC;
    if(!(nue->dato = malloc(tamDato)))
    {
        free(nue);
        return ERR_MALLOC;
    }
    memcpy(nue->dato,dato,tamDato);
    nue->tam = tamDato;
    nue->sig = *plista;

    *plista = nue;
    return EXITO;
}

int sacarFinalpioLista(tLista *plista,void* dato,unsigned tamDato)
{
    while((*plista)->sig)
        plista = &(*plista)->sig;

    memcpy(dato,(*plista)->dato,MIN((*plista)->tam,tamDato));
    free((*plista)->dato);
    free(*plista);
    *plista = NULL;
    return EXITO;
}

int verFinalLista(const tLista *plista, void* dato, unsigned tamDato)
{
    while((*plista)->sig)
        plista = &(*plista)->sig;
    memcpy(dato,(*plista)->dato,MIN((*plista)->tam,tamDato));
    return EXITO;
}

int insertarPosicionLista(tLista *plista, const void* dato, unsigned tamDato, unsigned pos)
{
    tNodo *nue;
    while(pos && *plista)
    {
        plista = &(*plista)->sig;
        pos--;
    }
    if(pos)
        return POS_INVALIDA;

    if (!(nue = (tNodo*)malloc(sizeof(tNodo))))
        return ERR_MALLOC;
    if(!(nue->dato = malloc(tamDato)))
    {
        free(nue);
        return ERR_MALLOC;
    }
    memcpy(nue->dato,dato,tamDato);
    nue->tam = tamDato;
    nue->sig = *plista;

    *plista = nue;
    return EXITO;
}

int sacarPosicionLista(tLista *plista, void* dato, unsigned tamDato, unsigned pos)
{
    tNodo *elim;
    while (pos && *plista)
    {
        plista = &(*plista)->sig;
        pos--;
    }
    if(pos || !*plista)
        return POS_INVALIDA;

    elim = *plista;
    *plista = elim->sig;
     memcpy(dato,elim->dato,MIN(elim->tam,tamDato));
    free(elim->dato);
    free(elim);
    *plista = NULL;
    return EXITO;
}

int verPosicionLista(const tLista *plista, void* dato, unsigned tamDato, unsigned pos)
{

    while (pos && *plista)
    {
        plista = &(*plista)->sig;
        pos--;
    }
    if(pos || !*plista)
        return POS_INVALIDA;

     memcpy(dato,(*plista)->dato,MIN((*plista)->tam,tamDato));

    return EXITO;
}

void recorrerLista( tLista *pLista, void accion(void*, void*), void *param)
{
    while(*pLista)
    {
        accion((*pLista)->dato, param);
        pLista = &(*pLista)->sig;
    }
}
