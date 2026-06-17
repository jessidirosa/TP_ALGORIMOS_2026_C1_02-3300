#include "config.h"
#include "juego.h"
#include "tablero.h"
int main()
{
    tConfig config;
    srand(time(NULL));
    tArbol arbol;

    crearArbol(&arbol);

    if(!indiceArchivoJugadores(&arbol, ARCH_JUGADORES, ARCH_INDICE))
        printf("No se pudo crear el indice.");

    cargarConfig(ARCH_CONFIG, &config);
    menu(&config, &arbol);
    actualizarIndice(&arbol);

    return 0;
}

