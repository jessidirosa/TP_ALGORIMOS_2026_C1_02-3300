#include "config.h"
#include "juego.h"
#include "tablero.h"


int main()
{
    tConfig config;
    srand(time(NULL));


    if(cargarConfig(ARCH_CONFIG, &config))
        printf("la configuracion se cargo correctamente:\nPosiciones Totales: %u\nVidas: %u\nBandidos: %u\nPremios: %u\nVidas Extras: %u\nOasis: %u\nTormentas: %u\n", config.cantidad_posiciones, config.vidas_inicio, config.maximo_bandidos, config.maximo_premios, config.maximo_vidas_extra, config.maximo_oasis, config.maximo_tormentas);
    else
        printf("error al abrir archivo");


    ///prueba de generacion de tablero en lista circular doble
    tListaD l;
    crearListaD(&l);

    menu(&config);
    return 0;
}
