#include <stdio.h>
#include <stdlib.h>
#include "FuncionesReversi.c"


int main() {
    char opcion = 0;
    int size;
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);

    printf("\ncomenzar juego\nPRESS ENTER\n");
    scanf("%c", &opcion);

    printf("Escribe el numero de n para el tablero nxn a continuacion (el numero debe ser par mayo a 4):");
    scanf("%d", &size);

    printf("\n");

    GAME juego = IniciarTablero(size);

    do {
        do {
            MostrarTablero(juego,size);
            MovimientosDisponibles(&juego,size);
            printf("\n");
            MostrarTablero(juego,size);
            RealizarMovimiento(&juego,size);
            LimpiarTablero(&juego,size);
        }while (EndGame(juego,size));

        printf("volver a jugar?\n");
        scanf("%c", &opcion);
    }while(opcion == 's');

    free(juego.tablero);

    return 0;
}
