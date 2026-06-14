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

void escena_perdida_turno(int oro) {
    printf("+===========================================================+\n");
    printf("|       ~ ~ ~   R E F U G I O   I N U S U A L   ~ ~ ~       |\n");
    printf("|                                                           |\n");
    printf("|  ///      _..---.._                 _______           /// |\n");
    printf("|         .'         '.              [ CUEVA ]              |\n");
    printf("|        /    (o_o)    \\             [  $ 2  ]              |\n");
    printf("|       |    >-(_)-<    |             `--|--`               |\n");
    printf("|  ///  |     /   \\     |                |                  |\n");
    printf("|       |   -'-   -'-   |     ($)        |          [J]     |\n");
    printf("|       |_______________|______|_________|____              |\n");
    printf("|                                                           |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| >> La tormenta empeora y necesitas refugio urgente...     |\n");
    printf("| >> Una lagartija negociante te alquila su cueva. (-2 ORO) |\n");
    printf("| >> Oro restante: %.2d                                     |\n",oro);
    printf("| >> Es una pena, el viaje por el desierto no seguira hoy.  |\n");
    printf("+-----------------------------------------------------------+\n");
};

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
    printf("| >> Las tormentas de arena continuan, pero el oasis te protege.|\n");
    printf("+---------------------------------------------------------------+\n");
}


void escena_bandido(int vidas) {
    limpiar();
    printf("+===========================================================+\n");
    printf("|       X X X    B A N D I D O S !!!    X X X               |\n");
    printf("|                                                           |\n");
    printf("|          \\|/                                              |\n");
    printf("|         (o_o)                                             |\n");
    printf("|       __/|B|\\__     <----  ATAQUE  ---->     [J]          |\n");
    printf("|          / \\                                              |\n");
    printf("|         _| |_                                             |\n");
    printf("|                                                           |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| >> Un bandido emboscó tu caravana!                        |\n");
    if(vidas > 1)
        printf("| >> Perdiste 1 vida, te quedan %d vidas.                    |\n", vidas);
    else
        printf("| >> Perdiste 1 vida, te queda %d vida.                      |\n", vidas);
    printf("+-----------------------------------------------------------+\n");
}

void escena_oasis() {
    limpiar();
    printf("+===========================================================+\n");
    printf("|               ~ ~ ~   O A S I S   ~ ~ ~                   |\n");
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
    printf("| >> Llegas a un oasis. Estas protegido.                    |\n");
    printf("+-----------------------------------------------------------+\n");
}

void escena_premio(int oro) {
    limpiar();
    printf("+===========================================================+\n");
    printf("|     * * *   P R E M I O   E N C O N T R A D O   * * *     |\n");
    printf("|                                                           |\n");
    printf("|                       _________                           |\n");
    printf("|                      /         \\                          |\n");
    printf("|                     |   $   $   |                         |\n");
    printf("|                      \\____V____/       +%.2d ORO            |\n", oro);
    printf("|                       |||||||||                           |\n");
    printf("|                      /         \\                          |\n");
    printf("|                     '-----------'                         |\n");
    printf("|                         [J]                               |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| >> Un mercader te recompensa por tu valentia!             |\n");
    printf("+-----------------------------------------------------------+\n");
}


void escena_vida_extra() {
    limpiar();
    printf("+===========================================================+\n");
    printf("|          + + +   V I D A   E X T R A   + + +              |\n");
    printf("|                                                           |\n");
    printf("|                          ___                              |\n");
    printf("|                         [_O_]                             |\n");
    printf("|                         /   \\                             |\n");
    printf("|                        /     \\         +1 VIDA            |\n");
    printf("|                       |  (+)  |                           |\n");
    printf("|                       | ~ ~ ~ |                           |\n");
    printf("|                        \\_____/                            |\n");
    printf("|                                                           |\n");
    printf("|                                              [J]          |\n");
    printf("|                                                           |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| >> Encuentras una pocion curativa en el camino...         |\n");
    printf("| >> Recuperaste 1 vida                                     |\n");
    printf("+-----------------------------------------------------------+\n");
}

void escena_defensa_oasis() {
    limpiar();
    printf("+===========================================================+\n");
    printf("|       X X X   A T A Q U E   B L O Q U E A D O   X X X     |\n");
    printf("|                                                           |\n");
    printf("|        \\|/                 _______                        |\n");
    printf("|       (>_<)               |  ___  |                       |\n");
    printf("|      __/|B|\\__   - - ->   | |   | |         [J]           |\n");
    printf("|        / \\                | | O | |                       |\n");
    printf("|       _| |_               | |___| |                       |\n");
    printf("|                            \\_____/                        |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| >> Un bandido te ataco, pero el oasis te protege!         |\n");
    printf("| >> No has perdido vidas, pero pierdes el escudo del oasis.|\n");
    printf("+-----------------------------------------------------------+\n");
}

void escena_game_over() {
    limpiar();
    printf("+===========================================================+\n");
    printf("|     X X X   F I N   D E   L A   P A R T I D A   X X X     |\n");
    printf("|                                                           |\n");
    printf("|                        _______                            |\n");
    printf("|                       /       \\           _______         |\n");
    printf("|                      |  R I P  |         [ HONOR ]        |\n");
    printf("|                      |         |         [  + 1  ]        |\n");
    printf("|                      |         |          `--|--`         |\n");
    printf("|                      |         |             |            |\n");
    printf("|                   ~ ~~~~~~~~~~~~~ ~ ~ ~~~~~~~~~ ~         |\n");
    printf("|                                              [J]          |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| >> Un bandido te atrapo! No tenes mas vidas...            |\n");
    printf("| >> Por tu valentia obtenes 1 punto(oro) de honor.         |\n");
    printf("+-----------------------------------------------------------+\n");
}


void escena_dia_normal() {
    limpiar();
    printf("+===========================================================+\n");
    printf("|          - - -   D I A   T R A N Q U I L O   - - -        |\n");
    printf("|                                                           |\n");
    printf("|                \\_|_/                                      |\n");
    printf("|              ---( )---                                    |\n");
    printf("|                / | \\                                      |\n");
    printf("|                                          _                |\n");
    printf("|              _.-._                     _-(_)-_            |\n");
    printf("|           .-'     '-.               .-'       '-.  [J]    |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| >> Un dia normal bajo el sol del inmenso desierto.        |\n");
    printf("| >> La caravana avanza sin contratiempos.                  |\n");
    printf("+-----------------------------------------------------------+\n");
}

void escena_victoria(int puntos) {
    limpiar();
    printf("+===========================================================+\n");
    printf("|     * * * V I C T O R I A   A L C A N Z A D A   * * *     |\n");
    printf("|                                                           |\n");
    printf("|                     ___________                           |\n");
    printf("|                    '._==_==_=_.'                          |\n");
    printf("|                    .-\\:      /-.                          |\n");
    printf("|                   | (|:.     |) |                         |\n");
    printf("|                    '-|:.     |-'            [J]           |\n");
    printf("|                      \\::.    /                            |\n");
    printf("|                       '::. .'                             |\n");
    printf("|                         ) (                               |\n");
    printf("|                       _.' '._                             |\n");
    printf("|                      `-------`                            |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| >> Has cruzado el desierto y llegado a tu destino!        |\n");
    if(puntos > 1)
        printf("| >> Obtuviste %d puntos por completar la travesia!          |\n",puntos);
    else
        printf("| >> Obtuviste %d punto por completar la travesia!           |\n",puntos);
    printf("| >> FELICITACIONES! GANASTE EL JUEGO!                      |\n");
    printf("+-----------------------------------------------------------+\n");
}
