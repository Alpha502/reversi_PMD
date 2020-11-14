
#include <stdio.h>
#define size 8

#ifndef FUNCIONESREVERSI_H_
#define FUNCIONESREVERSI_H_


struct GameState{
    char tablero[size][size];
    int turno;
    char JugadorActual;
    char Oponente;
};
typedef  struct GameState GAME;
struct coord{
    int x;
    int y;
};
typedef struct coord COORD;

GAME IniciarTablero();
void MostrarTablero(GAME Juego);
void EscogerTurnoJugador(GAME *Juego);
int MovimientosDisponibles(GAME *Juego);
void RealizarMovimiento(GAME *Juego);
COORD ObtenerCoordenadas(GAME Juego);
void LimpiarTablero(GAME * Juego);

#endif /* FUNCIONESREVERSI_H_ */