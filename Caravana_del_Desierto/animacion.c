#include "animacion.h"
#include "juego.h"
void limpiar(void) {
    system("cls");
}
void escena_tormenta(int vidas, int puntos) {
    limpiar();
    printf("+===========================================================+\n");
    printf("|     !!!   T O R N A D O   D E   A R E N A   !!!          |\n");
//    hud(vidas, oro, agua);
    printf("|                                                           |\n");
    printf("|      %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%      |\n");
    printf("|       %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%       |\n");
    printf("|         %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%         |\n");
    printf("|           %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%           |\n");
    printf("|             %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%             |\n");
    printf("|               %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%               |\n");
    printf("|                 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                 |\n");
    printf("|                   %%%%%%%%%%%%%%%%%%%%%%%%%%                   |\n");
    printf("|                     %%%%%%%%%%%%%%%%%%                     |\n");
    printf("|                       %%%%%%%%%%                       |\n");
    printf("|                         %%%%                         |\n");
    printf("|              [C]         vv         ~ ~ ~                 |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| >>            El tornado azota la caravana.               |\n");
    printf("+-----------------------------------------------------------+\n");
}

void escena_bandido(int vidas, int oro) {
    limpiar();
    printf("+===========================================================+\n");
    printf("|       X X X    B A N D I D O S !!!    X X X              |\n");
//    hud(vidas, oro, agua);
    printf("|                                                           |\n");
    printf("|         \\|/                                               |\n");
    printf("|        (o_o)                                              |\n");
    printf("|       __/|B|\\__     <----  ATAQUE  ---->     [C]          |\n");
    printf("|          / \\                                              |\n");
    printf("|         _| |_                                             |\n");
    printf("|                                                           |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| >> Un bandido emboscó tu caravana!                        |\n");
    printf("| >> Perdiste 1 vida                                        |\n");
    printf("+-----------------------------------------------------------+\n");
}

void escena_oasis(int vidas, int oro) {
    limpiar();
    printf("+===========================================================+\n");
    printf("|            ~ ~ ~   O A S I S   ~ ~ ~                      |\n");
//    hud(vidas, oro, agua);
    printf("|                                                           |\n");
    printf("|                      __ _.--..--._ ___                    |\n");
    printf("|                  .-''            ''-.                     |\n");
    printf("|                .'  .-.        .-.   '.                    |\n");
    printf("|               /   (   )      (   )    \\                   |\n");
    printf("|              |   .-'  '.    .'  '-.    |                  |\n");
    printf("|               \\ (        \\/        ) /                    |\n");
    printf("|                '.\\        ||        /.'                   |\n");
    printf("|                   \\\\      ||      //                      |\n");
    printf("|                    ||     ||     ||                       |\n");
    printf("|                    ||     ||     ||                       |\n");
    printf("|                    ||     ||     ||                       |\n");
    printf("|       ~ ~ ~ ~ ~ ~ ~~~~~~~~~~~~~~~ ~ ~ ~ ~ ~              |\n");
    printf("|      ~  ~  ~  ~  [C]  ~  ~  ~  ~  ~  ~  ~  ~             |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| >> Llegas a un oasis. Estas protegido                     |\n");
    printf("+-----------------------------------------------------------+\n");
}

void escena_premio(int vidas, int oro) {
    limpiar();
    printf("+===========================================================+\n");
    printf("|     * * *   P R E M I O   E N C O N T R A D O   * * *    |\n");
//    hud(vidas, oro, agua);
    printf("|                                                           |\n");
    printf("|                       _________                           |\n");
    printf("|                      /         \\                          |\n");
    printf("|                     |   $   $   |        +1 VIDA          |\n");
    printf("|                      \\____V____/         +60 ORO          |\n");
    printf("|                       |||||||||                           |\n");
    printf("|                      /         \\                          |\n");
    printf("|                     '-----------'                         |\n");
    printf("|                         [C]                               |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| >> Un mercader te recompensa por tu valentia!             |\n");
    printf("+-----------------------------------------------------------+\n");
}
