#include "raylib.h"
#include "FuncionesReversi.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef REVERSI_GRAPH_H
#define REVERSI_GRAPH_H

void StartBoard(int size);
void AddText(GAME Juego, int size);
void DrawTokens(GAME Juego, int size);
COORD Distancias(int size);
void DrawGame();
void DrawRival(int Rival);
void DrawOption(int x, int y, int tam);


#endif //REVERSI_GRAPH_H
