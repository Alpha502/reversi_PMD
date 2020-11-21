#include <stdio.h>
#include "Graph.h"
#include "FuncionesReversi.h"


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
    InitWindow(1000, 650, "INFINIREVERSI");
    while (!WindowShouldClose()) {
        BeginDrawing();
        StartBoard(size);
        DrawTokens(juego, size);
        AddText(juego, size);
        EndDrawing();
/*
        do {
            while (EndGame(juego, size)) {
                MostrarTablero(juego, size);
                MovimientosDisponibles(&juego, size);
                printf("\n");
                MostrarTablero(juego, size);
                RealizarMovimiento(&juego, size);
                LimpiarTablero(&juego, size);
            }

            printf("volver a jugar?\n");
            scanf("%c", &opcion);
        } while (opcion == 's');

        free(juego.tablero);

*/    }
    CloseWindow();
    return 0;
}