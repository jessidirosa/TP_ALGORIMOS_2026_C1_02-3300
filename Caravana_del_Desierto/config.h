#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include "constantes.h"

#define CAMPO_1 "cantidad_posiciones"
#define CAMPO_2 "vidas_inicio"
#define CAMPO_3 "maximo_bandidos"
#define CAMPO_4 "maximo_premios"
#define CAMPO_5 "maximo_vidas_extra"
#define CAMPO_6 "maximo_oasis"
#define CAMPO_7 "maximo_tormentas"


typedef struct
{
    unsigned cantidad_posiciones; //número máximo de posiciones en el tablero.
    unsigned vidas_inicio; //cantidad de vidas iniciales.
    unsigned maximo_bandidos; //número de bandidos a distribuir en el tablero.
    unsigned maximo_premios; //número de premios a distribuir en el tablero.
    unsigned maximo_vidas_extra; //cantidad de vidas extra a distribuir en el tablero.
    unsigned maximo_oasis; //número de oasis a distribuir en el tablero.
    unsigned maximo_tormentas; //número de tormentas a distribuir en el tablero.

}tConfig;


///podemos pedir la configuracion tambien por pantalla agregando en el menu
///la opcion configuracion, y que cargue el archivo. No lo dice en el enunciado
///pero puede sumarnos y es relativamente facil. hice la carga de config para que
///no interese el orden en el que se indiquen los parametros para usarlo en ese caso.

//int crearArchConfig(const char* nombreArch, tConfig* config); //si pedimos por pantalla los parametros
int cargarConfig(const char* nombreArch, tConfig* c);
void trozarConfig(char* buffer, tConfig* c);




#endif // CONFIG_H_INCLUDED
