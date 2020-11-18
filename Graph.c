#include "raylib.h"
#include "Graph.h"


void StartBoard() {
    ClearBackground(BLUE);
    DrawRectangle(50, 50, 700, 550, GREEN);
    int DistanciaEntreLineas = 700/10;
    int DistanciaEntreFilas = 550/10;
    int PosFilas = 50;
    int PosLinea = 50;
    for (int i = 0; i <= 10; ++i) {
        DrawLine(PosLinea, 50, PosLinea, 600, BLACK);
        PosLinea += DistanciaEntreLineas;
    }
    for (int i = 0; i <= 10; ++i) {
        if(i == 20){
            DrawLine(50, 600, 750, 600, BLACK);
        } else {
            DrawLine(50, PosFilas, 750, PosFilas, BLACK);
            PosFilas += DistanciaEntreFilas;
        }
    }
}

void AddText(){
    DrawText("INFINIREVERSI", GetScreenWidth()/2 -150, 10, 20, BLACK);
    DrawText("MARCADOR", 800, 100, 20, BLACK);
    DrawText("Puntos jugador Blanco", 800, 200, 15, BLACK);
    DrawText("Puntos Jugador Negro", 800, 400, 15, BLACK);
}

