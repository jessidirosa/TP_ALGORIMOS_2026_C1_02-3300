#include "tablero.h"
#include "config.h"
#include "constantes.h"
void generarTablero_solucionTXT(tConfig *c)
{

    char tablero[100];
    for(int i=0; i< (int)c->cantidad_posiciones; i++)
    {
        tablero[i]='.';
    }

    tablero[0] = 'I';
    tablero[c->cantidad_posiciones - 1] = 'S';
    colocarElemAleatorios_solucionTXT(tablero, c->cantidad_posiciones, 'B', c->maximo_bandidos);
    colocarElemAleatorios_solucionTXT(tablero, c->cantidad_posiciones, 'P', c->maximo_premios);
    colocarElemAleatorios_solucionTXT(tablero, c->cantidad_posiciones, 'V', c->maximo_vidas_extra);
    colocarElemAleatorios_solucionTXT(tablero, c->cantidad_posiciones, 'O', c->maximo_oasis);
    colocarElemAleatorios_solucionTXT(tablero, c->cantidad_posiciones, 'T', c->maximo_tormentas);

    guardarTablero_solucionTXT(tablero,c->cantidad_posiciones);
    mostrarTablero_solucionTXT();
}
int mostrarTablero_solucionTXT()
{
    char linea[MAX_BUF];
    FILE *pf = fopen(ARCH_TABLERO,"r");
    if(!pf)
    {
        printf("\n error al abrir el archivo carvana.txt al leerse");
        return ERR_ARCH;
    }
    printf("\n-----TABLERO-----\n");
    while(fgets(linea,MAX_BUF,pf) != NULL)
    {
        printf("%s",linea);
    }
    fclose(pf);
    return TODO_OK;
}
void colocarElemAleatorios_solucionTXT(char tablero[], int n, char elemento, int cantidad)
{
    int puestos = 0;

    while (puestos < cantidad)
    {
        int pos = rand() % n;

        if (tablero[pos] == '.' && pos != 0 && pos != n - 1)
        {
            tablero[pos] = elemento;
            puestos++;
        }
    }
}
int guardarTablero_solucionTXT(char tablero[], int n)
{
    FILE *f = fopen(ARCH_TABLERO, "w");
    if(!f)
    {
        printf("\nError al abrir el archivo caravana.txt al generarse");
        return ERR_ARCH;
    }
    for (int i = 0; i < n; i++)
    {
        fprintf(f, "%02d:%c\n", i + 1, tablero[i]);
    }
    printf("\nTablero generado");
    fclose(f);
    return TODO_OK;
}


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
//    cargarArchCaravana(l);

    return TODO_OK;
}

/*void mostrarTablero(const void* dato, int num)
{
    tCasilla* c = (tCasilla*)dato;

    if (c->tieneJ)
    {
        if (c->tipo == '.')
            printf("%.2d:J  <--\n", num);
        else
            printf("%.2d:[%c J]  <--\n", num, c->tipo);
    }
    else
        printf("%.2d:%c\n", num, c->tipo);
}*/

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
