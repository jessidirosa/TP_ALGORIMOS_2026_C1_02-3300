#include "config.h"
#include "juego.h"
#include "tablero.h"


int main()
{
    tConfig config;
    srand(time(NULL));


    if(cargarConfig(ARCH_CONFIG, &config))
        printf("la configuracion se cargo correctamente:\n%u\n%u\n%u\n%u\n%u\n%u\n%u\n", config.cantidad_posiciones, config.vidas_inicio, config.maximo_bandidos, config.maximo_premios, config.maximo_vidas_extra, config.maximo_oasis, config.maximo_tormentas);
    else
        printf("error al abrir archivo");


    ///prueba de generacion de tablero en lista circular doble
    tListaD l;
    crearListaD(&l);

    if(!generarTablero(&config, &l))
        printf("no se pudo generar el tablero\n");
    else
    {
        printf("Ruta:\n");
        recorrerListaDobleIzqADer(&l, mostrarTablero);
        printf("\n\n");
    }

    menu(&config);
    return 0;
}
