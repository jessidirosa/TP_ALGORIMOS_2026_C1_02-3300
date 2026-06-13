#include "arbol.h"

void crearArbol(tArbol* arbol)
{
    (*arbol) = NULL;
}

int ponerEnArbol(tArbol* a, void* dato, unsigned tam, int cmp(const void*, const void*))
{
    tNodoA* nue;

    if(!(*a))
    {
        nue = malloc(sizeof(tNodoA));
        if(!nue)
            return SIN_MEM;

        nue->dato = malloc(tam);
        if(!nue->dato)
        {
            free(nue);
            return SIN_MEM;
        }

        nue->izq = NULL;
        nue->der = NULL;
        memcpy(nue->dato, dato, tam);
        nue->tam = tam;
        (*a) = nue;
        return TODO_OK;
    }

    if(cmp(dato, (*a)->dato) < 0)
        return ponerEnArbol(&(*a)->izq, dato, tam, cmp);

    else if(cmp(dato, (*a)->dato) > 0)
        return ponerEnArbol(&(*a)->der, dato, tam, cmp);

    return DUPLICADO;

}

void destruirArbol(tArbol* a)
{
    if((*a))
    {
        destruirArbol(&(*a)->izq);
        destruirArbol(&(*a)->der);

        free((*a)->dato);
        free(*a);
        (*a) = NULL;
    }
}

int compararIdx(const void* clave1, const void* clave2)
{
    tIndice* c1 = (tIndice*)clave1;
    tIndice* c2 = (tIndice*)clave2;

    return strcmp(c1->clave.alias, c2->clave.alias);
}


int indexarArchivoDesordenadoJugadores(tArbol* arbol, const char* nombreArch)
{
    tIndice indice;
    int insertado = 1;
    tArchJug jug;
    FILE* pf = fopen(nombreArch, "a+b");
    if(!pf)
        return ERR_ARCH;

    fseek(pf, 0L, SEEK_SET);
    indice.pos = 0;
    fread(&jug, sizeof(tArchJug), 1, pf);
    while(!feof(pf) && insertado == 1)
    {
        strcpy(indice.clave.alias, jug.nombre);
        insertado = ponerEnArbol(arbol, &indice, sizeof(tIndice), compararIdx);
        fread(&jug, sizeof(tArchJug), 1, pf);
        indice.pos++;
    }

    fclose(pf);
    return TODO_OK;
}

int cargarArchivoIndiceJugadores(tArbol* arbol, const char* archIdx)
{
    tIndice idx;
    FILE* pf = fopen(archIdx, "wb");
    if(!pf)
        return ERR_ARCH;

    cargarArbolAArchivoIndiceOrdenado(arbol, &idx, pf);

    destruirArbol(arbol);
    fclose(pf);
    return TODO_OK;
}

void cargarArbolAArchivoIndiceOrdenado(const tArbol* arbol, tIndice* idx, FILE* pf)
{
    if(!(*arbol))
        return;

    cargarArbolAArchivoIndiceOrdenado(&(*arbol)->izq, idx, pf);
    memcpy(idx, (*arbol)->dato, sizeof(tIndice));
    fwrite(idx, sizeof(tIndice), 1, pf);
    cargarArbolAArchivoIndiceOrdenado(&(*arbol)->der, idx, pf);
}

int cargarArchIndiceAArbolBalanceado(tArbol* arbol, const char* nombreArch)
{
    int inicio, fin;
    FILE* pf = fopen(nombreArch, "rb");
    if(!pf)
        return ERR_ARCH;

    fseek(pf, 0L, SEEK_END);
    fin = (ftell(pf)/sizeof(tIndice)) - 1;
    inicio = 0;
    insertarIdxEnArbolBalanceado(arbol, pf, inicio, fin);
    fclose(pf);
    return TODO_OK;
}

int insertarIdxEnArbolBalanceado(tArbol* arbol, FILE* pf, int inicio, int fin)
{
    tIndice idx;
    tNodoA* nue;
    int medio = (inicio + fin) / 2;

    if(inicio > fin)
        return FIN_CARGA;

    fseek(pf, medio * sizeof(tIndice), SEEK_SET);
    fread(&idx, sizeof(tIndice), 1, pf);
    nue = malloc(sizeof(tNodoA));
    if(!nue)
        return SIN_MEM;
    nue->dato = malloc(sizeof(tIndice));
    if(!nue->dato)
    {
        free(nue);
        return SIN_MEM;
    }

    nue->izq = NULL;
    nue->der = NULL;
    memcpy(nue->dato, &idx, sizeof(tIndice));
    nue->tam = sizeof(tIndice);
    (*arbol) = nue;

    insertarIdxEnArbolBalanceado(&(*arbol)->izq, pf, inicio, medio - 1);
    insertarIdxEnArbolBalanceado(&(*arbol)->der, pf, medio + 1, fin);

    return TODO_OK;

}

void cargarArbolAArchivoIndicePreorden(const tArbol* arbol, tIndice* idx, FILE* pf)
{
    if(!(*arbol))
        return;

    memcpy(idx, (*arbol)->dato, sizeof(tIndice));
    fwrite(idx, sizeof(tIndice), 1, pf);
    cargarArbolAArchivoIndicePreorden(&(*arbol)->izq, idx, pf);
    cargarArbolAArchivoIndicePreorden(&(*arbol)->der, idx, pf);
}

void recorrerPreorden(const tArbol* arbol, void accion(void*))
{
    if(!(*arbol))
        return;

    accion((*arbol)->dato);
    recorrerPreorden(&(*arbol)->izq, accion);
    recorrerPreorden(&(*arbol)->der, accion);
}

void recorrerInorden(const tArbol* arbol, void accion(void*))
{
    if(!(*arbol))
        return;

    recorrerInorden(&(*arbol)->izq, accion);
    accion((*arbol)->dato);
    recorrerInorden(&(*arbol)->der, accion);
}

int indiceArchivoJugadores(tArbol* arbol, const char* archJug, const char* archIdx)
{
    if(!indexarArchivoDesordenadoJugadores(arbol, ARCH_JUGADORES))// bajamos el archivo a un arbol
        return ERR_ARCH;

    if(!cargarArchivoIndiceJugadores(arbol, ARCH_INDICE))//con el mismo arbol cargamos el archivo indice
        return ERR_ARCH;

    destruirArbol(arbol);
    crearArbol(arbol);

    if(!cargarArchIndiceAArbolBalanceado(arbol, ARCH_INDICE)) //bajamos el archivo indice ordenado por clave, a un arbol
        return ERR_ARCH;

    return TODO_OK;
}

int compararClave(const void* alias, const void* idx)
{
    char* a = (char*)alias;
    tIndice* i = (tIndice*)idx;

    return strcmp(a, i->clave.alias);
}


int buscarEnIndice(tArbol* idx, const char* aliasJugador, tIndice* dato, int cmp(const void*, const void*))
{
    if(!(*idx))
        return NO_ENCONTRADO;

    if(!cmp(aliasJugador, (*idx)->dato))
    {
        memcpy(dato, (*idx)->dato, sizeof(tIndice));
        return ENCONTRADO;
    }

    return (buscarEnIndice((*idx)->izq, aliasJugador, dato, cmp) + buscarEnIndice((*idx)->izq, aliasJugador, dato, cmp));
}
