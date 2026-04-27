#include "cola.h"

void crearCola(tCola* c)
{
    c->pri = NULL;
}
int colaLlena(const tCola* c, unsigned cantBytes)
{
    return COLA_NOLLENA;
}
int colaVacia(const tCola* c)
{
    return c->pri == NULL? COLA_VACIA : COLA_NOVACIA;
}
void vaciarCola(tCola* c)
{
    tNodo* elim = c->pri;

    while(c->pri != NULL)
    {
        c->pri = elim->sig;

        free(elim->dato);
        free(elim);

        elim = c->pri;
    }

    c->ult = NULL;
}
int encolar(tCola* c,const void* d, unsigned cantBytes)
{
    tNodo* nue = malloc(sizeof(tNodo));
    if(!nue)
        return SIN_MEM;

    nue->dato = malloc(cantBytes);
    if(!nue->dato)
    {
        free(nue);
        return SIN_MEM;
    }

    memcpy(nue->dato,d,cantBytes);
    nue->sig = NULL;

    if(c->pri == NULL)
        c->pri = nue;
    else
        c->ult->sig = nue;

    c->ult = nue;

    return TODO_OK;
}

int desencolar(tCola* c, void* d, unsigned cantBytes)
{
    tNodo* elim = c->pri;

    if(c->pri == NULL)
        return COLA_VACIA;

    memcpy(d,elim->dato,MIN(cantBytes,elim->tam));

    c->pri = elim->sig;

    if(c->pri == NULL)
        c->ult = NULL;

    free(elim->dato);
    free(elim);

    return TODO_OK;
}

int verTope(tCola* c, void* d, unsigned cantBytes)
{
    tNodo* ppri = c->pri;
    if(c->pri == NULL)
        return COLA_VACIA;
    memcpy(d,ppri->dato,MIN(cantBytes,ppri->tam));


    return TODO_OK;
}
