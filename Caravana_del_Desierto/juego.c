#include "juego.h"

void menu()
{
    unsigned opcion;

    printf("------CARAVANA DEL DESIERTO------\n\n");
    printf("Seleccione la opcion deseada:\n");
    printf("1 - Iniciar partida\n");
    printf("2 - Ver ranking\n");
    printf("3 - Salir\n");
    //4 - configurar partida

    scanf("%u", &opcion);
    while(opcion != 1 && opcion != 2 && opcion != 3)
    {
        printf("Ingrese una opcion valida: ");
        scanf("%u", &opcion);
    }

    switch (opcion) {
    case 1:
        system("cls");
//        iniciarPartida();
        break;

    case 2:
        system("cls");
//        verRanking();
        break;

    case 3:
        break;
    }
}
