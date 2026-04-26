#include "config.h"
#include "juego.h"


int main()
{
    tConfig config;
    srand(time(NULL));

    if(cargarConfig(ARCH_CONFIG, &config))
        printf("la configuracion se cargo correctamente:\n%u\n%u\n%u\n%u\n%u\n%u\n%u\n", config.cantidad_posiciones, config.vidas_inicio, config.maximo_bandidos, config.maximo_premios, config.maximo_vidas_extra, config.maximo_oasis, config.maximo_tormentas);
    else
        printf("error al abrir archivo");


    menu();
    return 0;
}
