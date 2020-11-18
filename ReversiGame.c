#include <stdio.h>
#include "FuncionesReversi.h"

#define size 8

int main(){
    char opcion = 0;
    setbuf(stdin, NULL);
    setbuf(stdout,NULL);

    printf("\ncomenzar juego\nPRESS ENTER\n");
    scanf("%c",&opcion);
    GAME juego = IniciarTablero();

    do {


        do {
            MostrarTablero(juego);
            MovimientosDisponibles(&juego);
            printf("\n");
            MostrarTablero(juego);
            RealizarMovimiento(&juego);
            LimpiarTablero(&juego);
        }while (EndGame(juego));

        printf("volver a jugar?\n");
        scanf("%c", &opcion);
    }while(opcion == 's');
    return 0;
}