#include "tablero.h"
#include "config.h"
#include "constantes.h"
void generarTablero_solucionTXT(tConfig *c)
{

    char tablero[100];
    for(int i=0; i< (int)c->cantidad_posiciones;i++)
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
void colocarElemAleatorios_solucionTXT(char tablero[], int n, char elemento, int cantidad) {
    int puestos = 0;

    while (puestos < cantidad) {
        int pos = rand() % n;

        if (tablero[pos] == '.' && pos != 0 && pos != n - 1) {
            tablero[pos] = elemento;
            puestos++;
        }
    }
}
int guardarTablero_solucionTXT(char tablero[], int n) {
    FILE *f = fopen(ARCH_TABLERO, "w");
    if(!f)
    {
        printf("\nError al abrir el archivo caravana.txt al generarse");
        return ERR_ARCH;
    }
    for (int i = 0; i < n; i++) {
        fprintf(f, "%02d:%c\n", i + 1, tablero[i]);
    }
    printf("\nTablero generado");
    fclose(f);
    return TODO_OK;
}
