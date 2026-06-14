#include "lista.h"
void crearLista(tLista *plista)
{
    *plista = NULL;
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

//    if((*pl) && !cmp((*pl)->dato, dato) && sinDup)

    if((*pl) && cmp((*pl)->dato, dato) == 0 && sinDup == 0)
    {
        if(accion) //accion != NULL
            accion((*pl)->dato,dato);

        return DUPLICADO;
    }

    nue = malloc(sizeof(tNodo));
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


void vaciarLista(tLista* lista)
{
    tNodo* elim;

    while(*lista != NULL)
    {
        elim = *lista;
        *lista = (*lista)->sig;
        free(elim->dato);
        free(elim);
    }
}


