#include "Graph.h"
#include "iaminimax.h"
#include <stdlib.h>

COORD Distancias(int size){
    //Obtiene una distancia usada para medir las casillas del tablero de tamaño constante
    COORD Distances;
    Distances.x = 700/size;
    Distances.y = 550/size;
    return Distances;
}

void StartBoard(int size) {
    ClearBackground(BLUE);
    //Dibuja el rectangulo que actua como tablero en la pantalla
    DrawRectangle(50, 50, 700, 550, GREEN);
    COORD Distances = Distancias(size);
    //El tablero no inicia en 0, 0 asi que se inicializa en un punto mas cercano al centro
    int PosFilas = 50;
    int PosColumna = 50;
    //Ciclo que dibuja las columnas
    for (int i = 0; i <= size; ++i) {
        if(i == size){
            //Por ser pixeles enteros no pueden dividirse exactamente asi que la ultima linea termina donde esté
            //El final del rectangulo
            DrawLine(750, 50, 750, 600, BLACK);
        }
        else {
            DrawLine(PosColumna, 50, PosColumna, 600, BLACK);
            PosColumna += Distances.x;
        }
    }
    //Ciclo que dibuja las lineas
    for (int i = 0; i <= size; ++i) {
        if(i == size){
            //No se divide exactamente asi que la linea final debe ser donde termine el rectangulo
            DrawLine(50, 600, 750, 600, BLACK);
        } else {
            DrawLine(50, PosFilas, 750, PosFilas, BLACK);
            PosFilas += Distances.y;
        }
    }
}

void DrawTokens(GAME Juego, int size){
    //Se obtienen las distancias que debe haber entre casillas y se obtiene el punto medio
    COORD Distances = Distancias(size);
    int PosicionEnLaColumna = (50 + 50 + Distances.y)/2;
    for (int y = 0; y < size; ++y) {
        //Posicion en la fila habla de la ubicacion en X del ciclo mientras que colummna de la poscicion y
        int PosicionEnLaFila = (50 + 50 + Distances.x)/2;
        for (int x = 0; x < size; x++) {
            //Se recorre la matriz del tablero por completo y si encuentra un valor se dubija en su centro el circulo
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
    //Se dibuja en pantalla el turno y los puntos de cada jugador
    int jeugo = EndGame(Juego, size);
    int mov_disponibles=0;
    if (jeugo==0) {
        MovimientosDisponibles(&Juego,size);
        for (int i = 0; i<size;++i){
            for (int j = 0; j < size; ++j) {
                if (Juego.tablero[i][j]=='A'){
                    mov_disponibles++;
                }
            }
        }
        LimpiarTablero(&Juego,size);
        if (mov_disponibles==0){
            DrawText("El juego ha terminado!!", 770, 500, 15, BLACK);
        }
    }else if(Juego.turno%2 != 0){
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
    //Dibuja un circulo de color rojo donde se encuentre el jugador
    COORD distance = Distancias(tam);
    DrawCircle(x, y, distance.x/3, RED);
}

void DrawRival(int Rival){
    if(Rival%2 == 0){
        DrawText("Jugador Contra CPU", 300, 350, 20, BLACK);
    }
    else{
        DrawText("Jugador Contra Jugador", 300, 350, 20, BLACK);
    }
    DrawText("Presione enter para continuar", 300, 400, 20, BLACK);
}

void DrawGame(){
    //Se inicializa la pantalla
    InitWindow(1000, 650, "INFINIREVERSI");
    SetTargetFPS(60);
    //Declara las variables que se usaran en el juego como la poscicion del jugador, en que ventana nos encontramos y las distancias
    COORD PosicionMatriz;
    PosicionMatriz.x = 0;
    PosicionMatriz.y = 0;
    int WindowNo = 0;
    int tam = 8;
    int Rival = 0;
    GAME Juego;
    COORD distance;
    int PosicionEnLaColumna;
    int PosicionEnLaFila;

    while (!WindowShouldClose()) {
        if (WindowNo == 0) {
            if (IsKeyPressed(KEY_RIGHT)) {
                Rival += 1;
            }
            if (IsKeyPressed(KEY_LEFT)) {
                Rival -= 1;
            }
            if (IsKeyPressed(KEY_ENTER)) {
                WindowNo = 1;
            }
            BeginDrawing();
            ClearBackground(BLUE);
            DrawRival(Rival);
            EndDrawing();
        }
        //La ventana 1 determina el tamaño del juego con las felchas siendo este un numero par y tablero cuadrado
        if (WindowNo == 1) {
            if (IsKeyPressed(KEY_RIGHT) && tam != 150) {
                tam += 2;
            }
            if (IsKeyPressed(KEY_LEFT) && tam != 6) {
                tam -= 2;
            }
            //Si se presiona enter se pasa a la siguiente pantalla y se setean las variables con el valor del tamaño seleccionado
            if (IsKeyPressed(KEY_ENTER)) {
                if (Rival % 2 == 0) {
                    WindowNo = 2;
                } else {
                    WindowNo = 3;
                }
                distance = Distancias(tam);
                PosicionEnLaColumna = (50 + 50 + distance.y) / 2;
                PosicionEnLaFila = (50 + 50 + distance.x) / 2;
                Juego = IniciarTablero(tam);
            }

            BeginDrawing();
            ClearBackground(BLUE);
            DrawText(TextFormat("El tamaño del tablero sera: %i x %i", tam, tam), 350, 300, 20, BLACK);
            DrawText("Presione enter para comenzar", 350, 350, 20, BLACK);
            EndDrawing();
        }
        if (WindowNo == 2) {
            //Si hay movimientos disponibles de juega con las fechas del teclado moviendose por la matriz y la pantalla
            //si le toca al usuario:
            if (Juego.turno % 2 != 0) {
                MovimientosDisponibles(&Juego, tam);
                if (IsKeyPressed(KEY_DOWN) && PosicionMatriz.y != tam - 1) {
                    PosicionEnLaColumna += distance.y;
                    PosicionMatriz.y++;
                }
                if (IsKeyPressed(KEY_UP) && PosicionMatriz.y != 0) {
                    PosicionEnLaColumna -= distance.y;
                    PosicionMatriz.y--;
                }
                if (IsKeyPressed(KEY_RIGHT) && PosicionMatriz.x != tam - 1) {
                    PosicionEnLaFila += distance.x;
                    PosicionMatriz.x++;
                }
                if (IsKeyPressed(KEY_LEFT) && PosicionMatriz.x != 0) {
                    PosicionEnLaFila -= distance.x;
                    PosicionMatriz.x--;
                }
                //Cuando se presione enter se realiza un movimiento en la matriz y se ve reflejado en pantalla con el cambio de color
                if (IsKeyPressed(KEY_ENTER) && Juego.tablero[PosicionMatriz.y][PosicionMatriz.x] == 'A') {
                    RealizarMovimiento(&Juego, tam, PosicionMatriz.x, PosicionMatriz.y);
                    LimpiarTablero(&Juego, tam);
                }
            } else {
                //turno de la computadora
                //veo los movimientos validos para blanco (IA)
                MovimientosDisponibles(&Juego, tam);
                int mejorpuntuacion = 0;
                COORD mejormovida;
                //se crea una copia del tablero para no modificar el original
                //se le reserva memoria igual que al original
                GAME Copia;
                Copia.tablero = malloc(tam * sizeof(char *));
                for (int i = 0; i < tam; ++i) {
                    Copia.tablero[i] = malloc(tam * sizeof(char));
                }
                //se copian los valores del tablero original
                for (int y = 0; y < tam; y++) {
                    for (int x = 0; x < tam; x++) {
                        Copia.tablero[y][x] = Juego.tablero[y][x];
                    }
                }
                //se copian las demas caracteristicas del tablero
                Copia.turno = Juego.turno;
                Copia.JugadorActual = Juego.JugadorActual;
                Copia.Oponente = Juego.Oponente;
                //aqui se recorre el tablero del juego, si se encuentra una A (posibe movimiento de la IA
                //entonces se llama a minimax para que se ejecute y calcule es puntaje mas alto
                for (int y = 0; y < tam; y++) {
                    for (int x = 0; x < tam; x++) {
                        if (Juego.tablero[y][x] == 'A') {
                            //se realiza el movimiento a uno de los movimientos posibles
                            RealizarMovimiento(&Copia, tam, x, y);
                            /*
                             *
                             *
                             * IMPORTANTE LO DE ABAJO
                             * FALSE=IA
                             * TRUE=HUMANO
                             *
                             */
                            //se llama a minimax, false indica que es la computadora
                            int puntuacion = minimax(Copia, 0, false, tam);
                            Copia.turno--;
                            Copia.tablero[y][x] = 'A';
                            //se regresa el estado del tablero a como estaba antes de hacer el calculo de
                            //ese movimiento
                            //si la puntuacion (minimax en esa posicion) es mayor que mejor puntuacion
                            //mejor puntuacion al inicio es 0 entonces el primer movimiento siempre será mejor
                            if (puntuacion > mejorpuntuacion) {
                                mejorpuntuacion = puntuacion;
                                mejormovida.x = x;
                                mejormovida.y = y;
                                //se guardan las coordenadas
                            }
                        }
                    }
                }
                //se limpia el tablero y se realiza el movimiento en las mejores coordenadas (mayor puntuacion)
                LimpiarTablero(&Juego, tam);
                RealizarMovimiento(&Juego, tam, mejormovida.x, mejormovida.y);
                LimpiarTablero(&Juego, tam);
            }
            BeginDrawing();
            StartBoard(tam);
            DrawTokens(Juego, tam);
            DrawOption(PosicionEnLaFila, PosicionEnLaColumna, tam);
            AddText(Juego, tam);
            EndDrawing();
        }
        if (WindowNo == 3) {
            MovimientosDisponibles(&Juego, tam);
            if (IsKeyPressed(KEY_DOWN) && PosicionMatriz.y != tam - 1) {
                PosicionEnLaColumna += distance.y;
                PosicionMatriz.y++;
            }
            if (IsKeyPressed(KEY_UP) && PosicionMatriz.y != 0) {
                PosicionEnLaColumna -= distance.y;
                PosicionMatriz.y--;
            }
            if (IsKeyPressed(KEY_RIGHT) && PosicionMatriz.x != tam - 1) {
                PosicionEnLaFila += distance.x;
                PosicionMatriz.x++;
            }
            if (IsKeyPressed(KEY_LEFT) && PosicionMatriz.x != 0) {
                PosicionEnLaFila -= distance.x;
                PosicionMatriz.x--;
            }
            //Cuando se presione enter se realiza un movimiento en la matriz y se ve reflejado en pantalla con el cambio de color
            if (IsKeyPressed(KEY_ENTER) && Juego.tablero[PosicionMatriz.y][PosicionMatriz.x] == 'A') {
                LimpiarTablero(&Juego, tam);
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

    }
    CloseWindow();
    free(Juego.tablero);
}