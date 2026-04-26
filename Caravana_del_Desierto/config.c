#include "config.h"

int cargarConfig(const char* nombreArch, tConfig* c)
{
    char buffer[MAX_BUF];
    FILE* pf = fopen(nombreArch, "rt");
    if(!pf)
        return ERR_ARCH;

    while(fgets(buffer, sizeof(buffer), pf))
        trozarConfig(buffer, c);

    fclose(pf);
    return TODO_OK;
}

void trozarConfig(char* buffer, tConfig* c)
{
    char* aux = strrchr(buffer, ':');
    unsigned dato;

    aux++;
    sscanf(aux, "%u", &dato);
    aux--;
    (*aux) = '\0';

    if(!strcmp(buffer, CAMPO_1))
        c->cantidad_posiciones = dato;
    if(!strcmp(buffer, CAMPO_2))
        c->vidas_inicio = dato;
    if(!strcmp(buffer, CAMPO_3))
        c->maximo_bandidos = dato;
    if(!strcmp(buffer, CAMPO_4))
        c->maximo_premios = dato;
    if(!strcmp(buffer, CAMPO_5))
        c->maximo_vidas_extra = dato;
    if(!strcmp(buffer, CAMPO_6))
        c->maximo_oasis = dato;
    if(!strcmp(buffer, CAMPO_7))
        c->maximo_tormentas = dato;

}
