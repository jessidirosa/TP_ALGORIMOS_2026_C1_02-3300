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

int sacarFinalLista(tLista *plista,void* dato,unsigned tamDato)
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


int ordenarLista(tLista* pl, int cmp(const void*, const void*))
{
    tNodo** menor = pl;
    tNodo** pivot;
    tNodo* aux;

    if(!(*pl))
        return COLA_VACIA;

    while((*pl))
    {
        menor = pl;
        pivot = &(*pl)->sig;

        while((*pivot))
        {
            if(cmp((*pivot)->dato, (*menor)->dato) < 0)
                menor = pivot;

            pivot = &(*pivot)->sig;
        }

        if(pl != menor)
        {
            aux = (*menor);
            (*menor) = aux->sig;
            aux->sig = (*pl);
            (*pl) = aux;
        }

        pl = &(*pl)->sig;
    }

    return TODO_OK;
}


int insertarOrdenado(tLista* pl, const void* dato, unsigned tam, int sinDup, void accion(void*, const void*), int cmp(const void*, const void*))
{
    tNodo* nue;

    while((*pl) && cmp((*pl)->dato, dato) < 0)
        pl = &(*pl)->sig;

<<<<<<< HEAD
    if((*pl) && !cmp((*pl)->dato, dato) && sinDup)
=======
    if((*pl) && cmp((*pl)->dato, dato) == 0 && sinDup == 0)
>>>>>>> 5f343b94048d3365f5e4886eda73024427a99785
    {
        if(accion) //accion != NULL
            accion((*pl)->dato,dato);

        return DUPLICADO;
    }

    nue = malloc(sizeof(tNodo*));
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

    nue->sig = (*pl);
    (*pl) = nue;
    return TODO_OK;
}

void mostrarLista(tLista* l, void accion(const void* dato))
{
    while((*l))
    {
        accion((*l)->dato);
        l = &(*l)->sig;
    }
}

int ReducirAUnolosDuplicados(tLista* lista, int cmp(const void*,const void*), void accion (void*, const void*))
{
    tNodo** pclave = lista, **pl;
    tNodo* elim;


    if(*lista == NULL)
        return LISTA_VACIA;

    while(*pclave != NULL)
    {
        pl = pclave;
        pl = &((*pl)->sig);

        while(*pl != NULL)
        {
            if(cmp((*pclave)->dato,(*pl)->dato) == 0)
            {
                accion((*pclave)->dato,(*pl)->dato);
                elim = *pl;
                *pl = elim->sig;
                free(elim->dato);
                free(elim);
            }
            else
                pl = &((*pl)->sig);

        }
        pclave = &((*pclave)->sig);
    }
    return TODO_OK;
}


