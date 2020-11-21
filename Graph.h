#include "raylib.h"
#include "FuncionesReversi.h"
#include <stdio.h>

#ifndef REVERSI_GRAPH_H
#define REVERSI_GRAPH_H

void StartBoard(int size);
void AddText(GAME Juego, int size);
void DrawTokens(GAME Juego, int size);
COORD Distancias(int size);

#endif //REVERSI_GRAPH_H
