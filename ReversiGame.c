#include <stdio.h>

#define size 8

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


int main(){
    char opcion = 0;
    setbuf(stdin, NULL);
    setbuf(stdout,NULL);

    printf("\ncomenzar juego\nPRESS ENTER\n");
    scanf("%c",&opcion);
    GAME juego = IniciarTablero();

    do {


        do {
            MostrarTablero(juego);
            MovimientosDisponibles(&juego);
            printf("\n");
            MostrarTablero(juego);
            RealizarMovimiento(&juego);
            LimpiarTablero(&juego);
        }while (MovimientosDisponibles(&juego));

        printf("volver a jugar?\n");
        scanf("%c", &opcion);
    }while(opcion == 's');
    return 0;
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
    juego.tablero[size/2][size/2 - 1] = 'W';
    juego.turno = 1;

    return juego;
}

void MostrarTablero(GAME Juego) {
    for (int fila = 0; fila < size; fila++) {
        for (int columna = 0; columna < size; columna++) {
            if (Juego.tablero[fila][columna] == '0') {
                printf("|   |");
            } else {
                printf("| %c |", Juego.tablero[fila][columna]);
            }
        }
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
    int x = 4, y = 4;
    EscogerTurnoJugador(Juego);
    if (MovimientosDisponibles(Juego)){
        COORD coordenadas = ObtenerCoordenadas(*Juego);
        Juego->tablero[coordenadas.y][coordenadas.x] = Juego->JugadorActual;
        Juego->turno++;
        for (int AdyacentesEnY = -1; AdyacentesEnY < 2; AdyacentesEnY++){
            for(int  AdyacentesEnX = -1; AdyacentesEnX < 2; AdyacentesEnX++){
                if (y + AdyacentesEnY < 0 || y + AdyacentesEnY == size || x + AdyacentesEnX < 0
                    || x + AdyacentesEnX == size || (AdyacentesEnX == 0 && AdyacentesEnY == 0)){
                    continue;
                }
                if (Juego->tablero[y +AdyacentesEnY][x + AdyacentesEnX] == Juego->Oponente){
                    int MovimientoEnX = x + AdyacentesEnX;
                    int MovimientoEnY = y + AdyacentesEnY;
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
                            
                            while (x != MovimientoEnX || y != MovimientoEnY){
                                x += AdyacentesEnX;
                                y += AdyacentesEnY;
                                Juego->tablero[y][x] = Juego->JugadorActual;
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
    while(1) {
        while (1) {
            printf("\nIngrese cordenadas de una jugada posible x, y\n");
            scanf("%d, %d", &x, &y);
            if (x > 0 && x < size && y > 0 && y < size) {
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