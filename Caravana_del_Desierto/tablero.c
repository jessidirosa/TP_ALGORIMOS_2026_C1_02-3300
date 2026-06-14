#include "tablero.h"
#include "config.h"
#include "constantes.h"

int generarTablero(tConfig* c, tListaD* l)
{
    tCasilla cas;
    cas.tieneJ = 0;
    cas.tieneB = 0;

    unsigned i = 0, cantInsertados = 0;
    unsigned vacias;
    unsigned casillasEspeciales = c->maximo_bandidos + c->maximo_oasis + c->maximo_premios + c->maximo_tormentas + c->maximo_vidas_extra + 2;

    if(c->cantidad_posiciones < casillasEspeciales) //verificamos que la cantidad de posiciones no sea menor a las casillas especiales, y hacemos que el tablero sea jugable
    {
        vacias = casillasEspeciales;
        c->cantidad_posiciones = casillasEspeciales + vacias;
    }
    else
        vacias = c->cantidad_posiciones - casillasEspeciales;

    cas.tipo = '.';
    while(i<vacias && insertarEnPosicRelListaD(l, &cas, sizeof(tCasilla), rand() % (cantInsertados + 1)))
    {
        i++;
        cantInsertados++;
    }

    if(i < vacias)
        return SIN_MEM;

    i = 0;
    cas.tipo = 'B';
    while(i<c->maximo_bandidos &&  insertarEnPosicRelListaD(l, &cas, sizeof(tCasilla), rand() % (cantInsertados + 1)))
    {
        i++;
        cantInsertados++;
    }


    if(i < c->maximo_bandidos)
        return SIN_MEM;

    i = 0;
    cas.tipo = 'O';
    while(i<c->maximo_oasis &&  insertarEnPosicRelListaD(l, &cas, sizeof(tCasilla), rand() % (cantInsertados + 1)))
    {
        i++;
        cantInsertados++;
    }


    if(i < c->maximo_oasis)
        return SIN_MEM;

    i = 0;
    cas.tipo = 'P';
    while(i<c->maximo_premios &&  insertarEnPosicRelListaD(l, &cas, sizeof(tCasilla), rand() % (cantInsertados + 1)))
    {
        i++;
        cantInsertados++;
    }


    if(i < c->maximo_premios)
        return SIN_MEM;

    i = 0;
    cas.tipo = 'V';
    while(i<c->maximo_vidas_extra &&  insertarEnPosicRelListaD(l, &cas, sizeof(tCasilla), rand() % (cantInsertados + 1)))
    {
        i++;
        cantInsertados++;
    }


    if(i < c->maximo_vidas_extra)
        return SIN_MEM;

    i = 0;
    cas.tipo = 'T';
    while(i<c->maximo_tormentas &&  insertarEnPosicRelListaD(l, &cas, sizeof(tCasilla), rand() % (cantInsertados + 1)))
    {
        i++;
        cantInsertados++;
    }


    if(i < c->maximo_tormentas)
        return SIN_MEM;

    cas.tipo = 'I';
    if(!insertarAlInicioListaD(l, &cas, sizeof(tCasilla)))
        return SIN_MEM;

    cas.tipo = 'S';
    if(!insertarAlFinalListaD(l, &cas, sizeof(tCasilla)))
        return SIN_MEM;


    ///implementar:
    cargarArchCaravana(ARCH_TABLERO, l);

    return TODO_OK;
}

int cargarArchCaravana(const char* nombreArch, tListaD* l)
{
    tNodoD* act = (*l);
    tNodoD* ini;
    int num = 1;

    FILE* pf = fopen(nombreArch, "wt");
    if(!pf)
        return ERR_ARCH;

    if(!act)
        return VACIA;

    ini = act;
    while(((tCasilla*)ini->dato)->tipo != 'I')
        ini = ini->sig;

    fprintf(pf, "%.2d:%c\n", num, ((tCasilla*)ini->dato)->tipo);

    act = ini->sig;
    while(act != ini)
    {
        fprintf(pf, "%.2d:%c\n", num, ((tCasilla*)act->dato)->tipo);
        act = act->sig;
        num++;
    }

    fclose(pf);
    return TODO_OK;
}

void mostrarTablero(const void* dato, int num)
{
    tCasilla* c = (tCasilla*)dato;
    int i = 0;
    int impreso = 0;

    printf("%.2d:", num);

    if (c->tieneJ || c->tieneB > 0)
    {
        printf("[");

        if (c->tipo != '.')
        {
            printf("%c", c->tipo);
            impreso = 1;
        }

        if (c->tieneJ)
        {
            if (impreso)
                printf(" ");
            printf("J");
            impreso = 1;
        }

        i = 0;
        while (i < c->tieneB)
        {
            if (impreso) printf(" ");
            printf("B");
            impreso = 1;
            i++;
        }

        printf("]");

        if (c->tieneJ)
        {
            printf("  <--");
        }
        printf("\n");
    }
    else
    {
        printf("%c\n", c->tipo);
    }
}
