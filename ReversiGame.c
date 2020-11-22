#include "Graph.h"
#include "FuncionesReversi.h"


int main() {
    int size = 8;
    GAME juego = IniciarTablero(size);
    DrawGame(juego, size);
    free(juego.tablero);

    return 0;
}