#include <stdio.h>

#define size 8

struct GameState{
    char tablero[size][size];
    int turno;
};

typedef  struct GameState GAME;

GAME IniciarTablero();
void MostrarTablero(GAME Juego);
void Movimientos(GAME *Juego);


int main(){
    GAME juego = IniciarTablero();
    MostrarTablero(juego);
    Movimientos(&juego);
    printf("\n");
    MostrarTablero(juego);

    return 0;
}

GAME IniciarTablero(){
    GAME juego;
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            juego.tablero[y][x] = '0';
        }
    }
    juego.tablero[size/2 -1][size/2 - 1] = 'B';
    juego.tablero[size/2][size/2] = 'B';
    juego.tablero[size/2 -1][size/2] = 'W';
    juego.tablero[size/2][size/2 - 1] = 'W';
    juego.turno = 1;

    return juego;
}

void MostrarTablero(GAME Juego) {
    for (int fila = 0; fila < size; fila++) {
        for (int columna = 0; columna < size; columna++) {
            if (Juego.tablero[fila][columna] == '0') {
                printf("|   |");
            } else {
                printf("| %c |", Juego.tablero[fila][columna]);
            }
        }
        printf("\n");
    }
}

void Movimientos(GAME *Juego) {
    char JugadorActual, Oponente;
    if (Juego->turno % 2 != 0) {
        JugadorActual = 'B';
        Oponente = 'W';
    }
    else {
        JugadorActual = 'W';
        Oponente = 'B';
    }
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            if (Juego->tablero[y][x] != '0') {
                continue;
            }
            for (int AdyacentesEnY = -1; AdyacentesEnY < 2; ++AdyacentesEnY) {
                for (int AdyacentesEnX = -1; AdyacentesEnX < 2; ++AdyacentesEnX) {
                    if (y + AdyacentesEnY < 0 || y + AdyacentesEnY == size || x + AdyacentesEnX < 0 ||
                        x + AdyacentesEnX == size
                        || (AdyacentesEnY == 0 && AdyacentesEnX == 0)) {
                        continue;
                    }
                    if (Juego->tablero[y + AdyacentesEnY][x + AdyacentesEnX] == Oponente) {
                        int MovimientoEnX = x + AdyacentesEnX;
                        int MovimientoEnY = y + AdyacentesEnY;
                        while (1) {
                            MovimientoEnX += AdyacentesEnX;
                            MovimientoEnY += AdyacentesEnY;
                            if (Juego->tablero[MovimientoEnY][MovimientoEnX] == '0'){
                                break;
                            }
                            if (MovimientoEnX < 0 || MovimientoEnX >= size || MovimientoEnY < 0 ||
                                MovimientoEnY >= size) {
                                break;
                            }
                            if (Juego->tablero[MovimientoEnY][MovimientoEnX] == JugadorActual) {
                                Juego->tablero[y][x] = 'A';
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}
