#include "config.h"

int main()
{
    char archConfig[] = "config.txt";
    tConfig config;

    if(cargarConfig(archConfig, &config))
        printf("la configuracion se cargo correctamente:\n%u\n%u\n%u\n%u\n%u\n%u\n%u\n", config.cantidad_posiciones, config.vidas_inicio, config.maximo_bandidos, config.maximo_premios, config.maximo_vidas_extra, config.maximo_oasis, config.maximo_tormentas);
    else
        printf("error al abrir archivo");

    return 0;
}
