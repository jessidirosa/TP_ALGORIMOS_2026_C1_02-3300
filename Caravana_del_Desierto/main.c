#include "config.h"
#include "juego.h"
#include "tablero.h"

void mostrarIndice(void* elem);

int main()
{
    tConfig config;
    srand(time(NULL));
    tArbol arbol;

    crearArbol(&arbol);

    if(!indiceArchivoJugadores(&arbol, ARCH_JUGADORES, ARCH_INDICE))
        printf("No se pudo crear el indice."); /// prueba para ver estado de creacion del idx (despues lo borramos)

    recorrerInorden(&arbol, mostrarIndice);
    if(cargarConfig(ARCH_CONFIG, &config))
        printf("la configuracion se cargo correctamente:\nPosiciones Totales: %u\nVidas: %u\nBandidos: %u\nPremios: %u\nVidas Extras: %u\nOasis: %u\nTormentas: %u\n", config.cantidad_posiciones, config.vidas_inicio, config.maximo_bandidos, config.maximo_premios, config.maximo_vidas_extra, config.maximo_oasis, config.maximo_tormentas);
    else
        printf("error al abrir archivo");


    ///prueba de generacion de tablero en lista circular doble
    tListaD l;
    crearListaD(&l);

    menu(&config, &arbol);
    actualizarIndice(&arbol);

    return 0;
}

void mostrarIndice(void* elem)
{
    tIndice* idx = (tIndice*)elem;
    printf("%s  %d\n", idx->clave.alias, idx->pos);
}

