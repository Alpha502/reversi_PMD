#include <stdio.h>
#include <stdlib.h>

#ifndef FUNCIONESREVERSI_H_
#define FUNCIONESREVERSI_H_


struct GameState{
    char** tablero;
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

GAME IniciarTablero(int size);
void MostrarTablero(GAME Juego, int size);
void EscogerTurnoJugador(GAME *Juego);
int MovimientosDisponibles(GAME *Juego,int size);
void RealizarMovimiento(GAME *Juego,int size);
COORD ObtenerCoordenadas(GAME Juego,int size);
void LimpiarTablero(GAME * Juego,int size);
int EndGame(GAME Juego,int size);
COORD Puntos(GAME Juego,int size);

#endif /* FUNCIONESREVERSI_H_ */
