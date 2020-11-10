#include <stdio.h>

#define size 8

struct GameState{
    char tablero[size][size];
    int turno;
};

typedef  struct GameState GAME;

GAME IniciarTablero();
void MostrarTablero(char Tablero[size][size]);
void Movimientos(char Tablero[size][size], char movimiento[3], int  turno);


int main(){
    GAME juego = IniciarTablero();

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
    juego.tablero[size/2][size/2 - 1] = 'w';
    juego.turno = 0;

    return juego;
}

void MostrarTablero(char Tablero[size][size]) {
    for (int fila = 0; fila < size; fila++) {
        for (int columna = 0; columna < size; columna++) {
            if (Tablero[fila][columna] == 0) {
                printf("|   |");
            } else {
                printf("| %c |", Tablero[fila][columna]);
            }
        }
        printf("\n");
    }
}
