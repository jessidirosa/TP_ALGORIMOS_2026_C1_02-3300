#include "animacion.h"
#include "juego.h"
void limpiar(void) {
    system("cls");
}

void escena_tormenta() ///chatcito
{
    limpiar();

    printf("+============================================================+\n");
    printf("|      !!!   T O R N A D O   D E   A R E N A   !!!           |\n");
    printf("|                                                            |\n");
    printf("|      &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&           |\n");
    printf("|       &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&            |\n");
    printf("|        &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&             |\n");
    printf("|         &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&              |\n");
    printf("|          &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&               |\n");
    printf("|            &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&                 |\n");
    printf("|              &&&&&&&&&&&&&&&&&&&&&&&&&&&                   |\n");
    printf("|                &&&&&&&&&&&&&&&&&&&&&&&                     |\n");
    printf("|                  &&&&&&&&&&&&&&&&&&                        |\n");
    printf("|                    &&&&&&&&&&&&&&                          |\n");
    printf("|                      &&&&&&&&&&                            |\n");
    printf("|                         &&&&                               |\n");
    printf("|                          &&                                |\n");
    printf("|            [J]           vv         ~ ~ ~                  |\n");
    printf("+------------------------------------------------------------+\n");
    printf("| >> El tornado azota la caravana. Perdes un turno.          |\n");
    printf("+------------------------------------------------------------+\n");
}

void escena_tormenta_protegido()
{
    limpiar();

    printf("+===============================================================+\n");
    printf("|             O A S I S   S A L V A D O R                       |\n");
    printf("|                                                               |\n");
    printf("|          . . . . . . . . . . . . . . . . . .                  |\n");
    printf("|       . . . . . . . . . . . . . . . . . . . .                 |\n");
    printf("|                                                               |\n");
    printf("|                    ~ ~ ~ ~ ~ ~ ~                              |\n");
    printf("|                 ~ ~           ~ ~                             |\n");
    printf("|              ~ ~      [O][J]     ~ ~                          |\n");
    printf("|                 ~ ~           ~ ~                             |\n");
    printf("|                    ~ ~ ~ ~ ~ ~ ~                              |\n");
    printf("|                                                               |\n");
    printf("|                                                               |\n");
    printf("+---------------------------------------------------------------+\n");
    printf("| >> Las tormentas de arena continuan, pero el oasis te protege |\n");
    printf("+---------------------------------------------------------------+\n");
}


void escena_bandido(int vidas) {
    limpiar();
    printf("+===========================================================+\n");
    printf("|       X X X    B A N D I D O S !!!    X X X               |\n");
//    hud(vidas, oro, agua);
    printf("|                                                           |\n");
    printf("|          \\|/                                              |\n");
    printf("|         (o_o)                                             |\n");
    printf("|       __/|B|\\__     <----  ATAQUE  ---->     [J]          |\n");
    printf("|          / \\                                              |\n");
    printf("|         _| |_                                             |\n");
    printf("|                                                           |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| >> Un bandido emboscó tu caravana!                        |\n");
    printf("| >> Perdiste 1 vida, te quedan %d                          |\n", vidas);
    printf("+-----------------------------------------------------------+\n");
}

void escena_oasis() {
    limpiar();
    printf("+===========================================================+\n");
    printf("|               ~ ~ ~   O A S I S   ~ ~ ~                   |\n");
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
    printf("|       ~ ~ ~ ~ ~ ~ ~~~~~~~~~~~~~~~ ~ ~ ~ ~ ~               |\n");
    printf("|      ~  ~  ~  ~  [J]  ~  ~  ~  ~  ~  ~  ~  ~              |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| >> Llegas a un oasis. Estas protegido                     |\n");
    printf("+-----------------------------------------------------------+\n");
}

void escena_premio(int oro) {
    limpiar();
    printf("+===========================================================+\n");
    printf("|     * * *   P R E M I O   E N C O N T R A D O   * * *     |\n");
//    hud(vidas, oro, agua);
    printf("|                                                           |\n");
    printf("|                       _________                           |\n");
    printf("|                      /         \\                          |\n");
    printf("|                     |   $   $   |                         |\n");
    printf("|                      \\____V____/       +%d ORO          |\n", oro);
    printf("|                       |||||||||                           |\n");
    printf("|                      /         \\                          |\n");
    printf("|                     '-----------'                         |\n");
    printf("|                         [J]                               |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| >> Un mercader te recompensa por tu valentia!             |\n");
    printf("+-----------------------------------------------------------+\n");
}
