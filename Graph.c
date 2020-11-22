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
                DrawCircle(PosicionEnLaFila, PosicionEnLaColumna, Distances.x/3, ORANGE);
            }
            PosicionEnLaFila += Distances.x;
        }
        PosicionEnLaColumna += Distances.y;
    }
}

void AddText(GAME Juego, int size){
    if(Juego.turno%2 != 0){
        DrawText("Turno del Jugador Negro", 770, 500, 15, BLACK);
    }
    else{
        DrawText("Turno del Jugador Blanco", 770, 500, 15, BLACK);
    };
    DrawText("INFINIREVERSI", GetScreenWidth()/2 -150, 10, 20, BLACK);
    DrawText("MARCADOR", 800, 100, 20, BLACK);
    COORD points = Puntos(Juego, size);
    DrawText("Puntos jugador Blanco", 800, 150, 15, BLACK);
    DrawText(TextFormat("%i", points.y), 800, 200, 60, BLACK);
    DrawText("Puntos Jugador Negro", 800, 350, 15, BLACK);
    DrawText(TextFormat("%i", points.x), 800, 400, 60, BLACK);

}

void DrawOption(int x, int y, int tam){
    COORD distance = Distancias(tam);
    DrawCircle(x, y, distance.x/3, RED);
}

int DrawSizeWindow(){
    InitWindow(600, 500, "Tamaño");
    SetTargetFPS(30);
    int tamanio = 8;
    while (!WindowShouldClose()){
        if(IsKeyPressed(KEY_RIGHT) && tamanio != 50){
            tamanio += 2;
        }
        if(IsKeyPressed(KEY_LEFT) && tamanio != 6){
            tamanio -= 2;
        }
        if(IsKeyPressed(KEY_ENTER)){
            CloseWindow();
        }

        BeginDrawing();
        ClearBackground(BLUE);
        DrawText(TextFormat("El tamaño del tablero sera: %i x %i", tamanio, tamanio), 160, 250, 20, BLACK);
        EndDrawing();
    }
    return tamanio;
}

void DrawGame(GAME Juego, int tam){
    InitWindow(1000, 650, "INFINIREVERSI");
    SetTargetFPS(30);


    COORD distance = Distancias(tam);
    COORD PosicionMatriz;
    PosicionMatriz.x = 0;
    PosicionMatriz.y = 0;
    int PosicionEnLaColumna = (50 + 50 + distance.y)/2;
    int PosicionEnLaFila = (50 + 50 + distance.x)/2;

    while (!WindowShouldClose()) {
        MovimientosDisponibles(&Juego, tam);
        if (IsKeyPressed(KEY_DOWN) && PosicionMatriz.y != tam-1){
            PosicionEnLaColumna += distance.y;
            PosicionMatriz.y++;
        }
        if (IsKeyPressed(KEY_UP) && PosicionMatriz.y != 0){
            PosicionEnLaColumna -= distance.y;
            PosicionMatriz.y--;
        }
        if (IsKeyPressed(KEY_RIGHT) && PosicionMatriz.x != tam-1){
            PosicionEnLaFila += distance.x;
            PosicionMatriz.x++;
        }
        if (IsKeyPressed(KEY_LEFT) && PosicionMatriz.x != 0){
            PosicionEnLaFila -= distance.x;
            PosicionMatriz.x--;
        }
        if (IsKeyPressed(KEY_ENTER) && Juego.tablero[PosicionMatriz.y][PosicionMatriz.x] == 'A'){
            RealizarMovimiento(&Juego, tam, PosicionMatriz.x, PosicionMatriz.y);
            LimpiarTablero(&Juego, tam);
        }

        BeginDrawing();
        StartBoard(tam);
        DrawTokens(Juego, tam);
        DrawOption(PosicionEnLaFila, PosicionEnLaColumna, tam);
        AddText(Juego, tam);
        EndDrawing();
    }
    CloseWindow();
}

