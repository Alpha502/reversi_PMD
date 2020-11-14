#include"FuncionesReversi.h"

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
    int numero_fila =0;
    int numero_col = 0;
    for (int columna = 0; columna < size; columna++) {
        printf("  %d  ",numero_col+columna);
    }
    printf("\n");
    for (int fila = 0; fila < size; fila++) {
        for (int columna = 0; columna < size; columna++) {
            if (Juego.tablero[fila][columna] == '0') {
                printf("|   |");
            } else {
                printf("| %c |", Juego.tablero[fila][columna]);
            }
        }
        printf("%d", numero_fila + fila);
        printf("\n");
    }
}

int MovimientosDisponibles(GAME *Juego) {
    int CasillasDisponibles;
    EscogerTurnoJugador(Juego);
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
                    if (Juego->tablero[y + AdyacentesEnY][x + AdyacentesEnX] == Juego->Oponente) {
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
                            if (Juego->tablero[MovimientoEnY][MovimientoEnX] == Juego->JugadorActual) {
                                Juego->tablero[y][x] = 'A';
                                CasillasDisponibles++;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    return CasillasDisponibles;
}

void RealizarMovimiento(GAME *Juego) {
    EscogerTurnoJugador(Juego);
    if (MovimientosDisponibles(Juego)){
        COORD coordenadas = ObtenerCoordenadas(*Juego);
        Juego->tablero[coordenadas.y][coordenadas.x] = Juego->JugadorActual;
        Juego->turno++;
        for (int AdyacentesEnY = -1; AdyacentesEnY < 2; AdyacentesEnY++){
            for(int  AdyacentesEnX = -1; AdyacentesEnX < 2; AdyacentesEnX++){
                if (coordenadas.y + AdyacentesEnY < 0 || coordenadas.y + AdyacentesEnY == size || coordenadas.x + AdyacentesEnX < 0
                    || coordenadas.x + AdyacentesEnX == size || (AdyacentesEnX == 0 && AdyacentesEnY == 0)){
                    continue;
                }
                if (Juego->tablero[coordenadas.y +AdyacentesEnY][coordenadas.x + AdyacentesEnX] == Juego->Oponente){
                    int MovimientoEnX = coordenadas.x + AdyacentesEnX;
                    int MovimientoEnY = coordenadas.y + AdyacentesEnY;
                    while (1){
                        MovimientoEnY += AdyacentesEnY;
                        MovimientoEnX += AdyacentesEnX;
                        if (MovimientoEnX < 0 || MovimientoEnX >= size || MovimientoEnY < 0 || MovimientoEnY >= size){
                            break;
                        }
                        if (Juego->tablero[MovimientoEnY][MovimientoEnX] == '0'){
                            break;
                        }
                        if (Juego->tablero[MovimientoEnY][MovimientoEnX] == Juego->JugadorActual){
                            //quiza aqui esta el error ---------------------------------------------------------------------------------------------------------------------
                            //creo que falta implementar que se cambie el valor si esta entre dos---------------------------------------------------------------------------

                            while (coordenadas.x != MovimientoEnX || coordenadas.y != MovimientoEnY){
                                coordenadas.x += AdyacentesEnX;
                                coordenadas.y += AdyacentesEnY;
                                Juego->tablero[coordenadas.y][coordenadas.x] = Juego->JugadorActual;
                            }
                        }
                    }
                }
            }
        }
    }
    else{
        printf("\nNo hay jugadas disponibles\n");
        Juego->turno++;
    }
}

void LimpiarTablero(GAME * Juego){
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; x++) {
            if (Juego->tablero[y][x] == 'A'){
                Juego->tablero[y][x] = '0';
            }
        }
    }
}

void EscogerTurnoJugador(GAME *Juego){
    if (Juego->turno % 2 != 0) {
        Juego->JugadorActual = 'B';
        Juego->Oponente = 'W';
    }
    else {
        Juego->JugadorActual = 'W';
        Juego->Oponente = 'B';
    }
}

COORD ObtenerCoordenadas(GAME Juego){
    COORD coordenada;
    int x, y;
    printf("\n");
    printf("Es el turno de: %c", Juego.JugadorActual);
    printf("\n");
    while(1) {
        while (1) {
            printf("\nIngrese cordenadas de una jugada posible x, y\n");
            scanf("%d, %d", &x, &y);
            if (x >= 0 && x < size && y >= 0 && y < size) {
                break;
            }
        }
        if (Juego.tablero[y][x] == 'A') {
            break;
        }
    }
    coordenada.x = x;
    coordenada.y = y;
    return coordenada;
}

int EndGame(GAME Juego){
    int CasillasLibres = 0;
    for (int y = 0; y < size; y++){
        for (int x = 0; x < size; x++){
            if(Juego.tablero[y][x] == '0'){
                CasillasLibres++;
            }
        }
    }
    int JugadasTurnoActual = MovimientosDisponibles(&Juego);
    Juego.turno++;
    int  JugadasTurnoSiguiente = MovimientosDisponibles(&Juego);
    return (CasillasLibres && (JugadasTurnoActual || JugadasTurnoSiguiente));
}
