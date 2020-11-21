#include "raylib.h"
#include "Graph.h"

COORD Distancias(int size){
    COORD Distances;
    Distances.x = 700/size;
    Distances.y = 550/size;
    return Distances;
}
void StartBoard(int size) {
    ClearBackground(BLUE);
    DrawRectangle(50, 50, 700, 550, GREEN);
    COORD Distances = Distancias(size);
    int PosFilas = 50;
    int PosColumna = 50;
    for (int i = 0; i <= size; ++i) {
        if(i == size){
            DrawLine(750, 50, 750, 600, BLACK);
        }
        else {
            DrawLine(PosColumna, 50, PosColumna, 600, BLACK);
            PosColumna += Distances.x;
        }
    }
    for (int i = 0; i <= size; ++i) {
        if(i == size){
            DrawLine(50, 600, 750, 600, BLACK);
        } else {
            DrawLine(50, PosFilas, 750, PosFilas, BLACK);
            PosFilas += Distances.y;
        }
    }
}
void DrawTokens(GAME Juego, int size){
    COORD Distances = Distancias(size);
    int PosicionEnLaColumna = (50 + 50 + Distances.y)/2;
    for (int y = 0; y < size; ++y) {
        int PosicionEnLaFila = (50 + 50 + Distances.x)/2;
        for (int x = 0; x < size; x++) {
            if (Juego.tablero[y][x] == 'B'){
                DrawCircle(PosicionEnLaFila, PosicionEnLaColumna, Distances.x/3, BLACK);
            }
            if (Juego.tablero[y][x] == 'W'){
                DrawCircle(PosicionEnLaFila, PosicionEnLaColumna, Distances.x/3, WHITE);
            }
            if (Juego.tablero[y][x] == 'A'){
                DrawCircle(PosicionEnLaFila, PosicionEnLaColumna, Distances.x/3, LIGHTGRAY);
            }
            PosicionEnLaFila += Distances.x;
        }
        PosicionEnLaColumna += Distances.y;
    }
}

void AddText(GAME Juego, int size){
    DrawText("INFINIREVERSI", GetScreenWidth()/2 -150, 10, 20, BLACK);
    DrawText("MARCADOR", 800, 100, 20, BLACK);
    COORD points = Puntos(Juego, size);
    DrawText("Puntos jugador Blanco", 800, 200, 15, BLACK);
    DrawText(TextFormat("%i", points.y), 800, 250, 60, BLACK);
    DrawText("Puntos Jugador Negro", 800, 400, 15, BLACK);
    DrawText(TextFormat("%i", points.x), 800, 450, 60, BLACK);
}

