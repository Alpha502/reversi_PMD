#include "FuncionesReversi.h"
#include <stdio.h>
#include "raylib.h"



GAME IniciarTablero(int size){
    //Crear espacios de memoria para el tablero
    GAME juego;
    juego.tablero=malloc(size * sizeof(char*));
    for (int i = 0; i < size; ++i) {
        juego.tablero[i] = malloc(size * sizeof(char));
    }
    //Llenando el tablero de 0s
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            juego.tablero[y][x] = '0';
        }
    }
    //seteando las fichas del centro
    juego.tablero[size/2 -1][size/2 - 1] = 'B';
    juego.tablero[size/2][size/2] = 'B';
    juego.tablero[size/2 -1][size/2] = 'W';
    juego.tablero[size/2][size/2 - 1] = 'W';
    juego.turno = 1;

    return juego;
}

void MostrarTablero(GAME Juego,int size) {
    //Se documenta sola
    int numero_fila =0;
    int numero_col = 0;
    for (int columna = 0; columna < size; columna++) {
        if (columna>=10){
            printf(" %d  ",numero_col+columna);
        }else if (columna>=100){
            printf("%d  ",numero_col+columna);
        }else
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

int MovimientosDisponibles(GAME *Juego,int size) {
    int CasillasDisponibles;
    EscogerTurnoJugador(Juego);
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            //Recorriendo el tablero a ver si la casilla actual es disponible para jugada
            if (Juego->tablero[y][x] != '0') {
                continue;
            }
            //Si encontramos casilla vacia vamos a verificar si es posible
            for (int AdyacentesEnY = -1; AdyacentesEnY < 2; ++AdyacentesEnY) {
                for (int AdyacentesEnX = -1; AdyacentesEnX < 2; ++AdyacentesEnX) {
                    //Checo alrededores para saber si hay algun jugador cercas
                    if ((y + AdyacentesEnY) < 0 || (y + AdyacentesEnY) == size || (x + AdyacentesEnX) < 0 ||
                        (x + AdyacentesEnX) == size
                        || (AdyacentesEnY == 0 && AdyacentesEnX == 0)) {
                        continue;
                    }
                    //Si encontre un jugador debe ser un oponente
                    if (Juego->tablero[y + AdyacentesEnY][x + AdyacentesEnX] == Juego->Oponente) {
                        int MovimientoEnX = x + AdyacentesEnX;
                        int MovimientoEnY = y + AdyacentesEnY;
                        //Si era un oponente, ahora voy a recorrer en esa direccion
                        while (1) {
                            MovimientoEnX += AdyacentesEnX;
                            MovimientoEnY += AdyacentesEnY;
                            //Si me salgo del tablero enconces no es posible
                            if (MovimientoEnX < 0 || MovimientoEnX >= size || MovimientoEnY < 0 ||
                                MovimientoEnY >= size) {
                                break;
                            }
                            //Si al terminar el recorrido esta vacio no es disponible
                            if (Juego->tablero[MovimientoEnY][MovimientoEnX] == '0'){
                                break;
                            }
                            //Si al terminar el recorrido encuentro una ficha mia entonces esta disponible
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

void RealizarMovimiento(GAME *Juego,int size, int x, int y) {
    EscogerTurnoJugador(Juego);
    //Verificar si el jugador actual tiene jugadas disponibles
    if (MovimientosDisponibles(Juego,size)){
        //Conseguir una coordenada valida y transformarla
        Juego->tablero[y][x] = Juego->JugadorActual;
        Juego->turno++;
        //Ver hasta donde se hara y en que direcciones si y en cuales no
        for (int AdyacentesEnY = -1; AdyacentesEnY <= 1; AdyacentesEnY++){
            for(int  AdyacentesEnX = -1; AdyacentesEnX <= 1; AdyacentesEnX++){
                //Verificando si a los alrededores se puede evaluar
                if (y + AdyacentesEnY < 0 || y + AdyacentesEnY == size || x + AdyacentesEnX < 0
                    || x + AdyacentesEnX == size || (AdyacentesEnX == 0 && AdyacentesEnY == 0)){
                    continue;
                }
                //Si encuentro una ficha enemiga medire hasta donde puedo hacer captura
                if (Juego->tablero[y + AdyacentesEnY][x + AdyacentesEnX] == Juego->Oponente){
                    int MovimientoEnX = x;
                    int MovimientoEnY = y;
                    while (1){
                        //Me muevo en la dirección en la que encontre un oponente
                        MovimientoEnY += AdyacentesEnY;
                        MovimientoEnX += AdyacentesEnX;
                        //Checo que no llegue a un espacio no valido de memoria
                        if (MovimientoEnX < 0 || MovimientoEnX >= size || MovimientoEnY < 0 || MovimientoEnY >= size){
                            break;
                        }
                        //Checo que no me lleve a un espacio vacio
                        if (Juego->tablero[MovimientoEnY][MovimientoEnX] == '0'){
                            break;
                        }
                        //Si encuentro una ficha mia enconces me movere de regreso, hasta llegar a la ubicacion
                        //De la ficha que acabo de agregar
                        if (Juego->tablero[MovimientoEnY][MovimientoEnX] == Juego->JugadorActual) {
                            while (Juego->tablero[MovimientoEnY -= AdyacentesEnY][MovimientoEnX -= AdyacentesEnX] ==
                                   Juego->Oponente) {
                                Juego->tablero[MovimientoEnY][MovimientoEnX] = Juego->JugadorActual;
                            }
                            break;
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

void LimpiarTablero(GAME * Juego,int size){
    //Borrar As del mapa
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; x++) {
            if (Juego->tablero[y][x] == 'A'){
                Juego->tablero[y][x] = '0';
            }
        }
    }
}

void EscogerTurnoJugador(GAME *Juego){
    //Se determina quien es el jugador actual dependiendo del turno en que vayan, empieza siempre B
    if (Juego->turno % 2 != 0) {
        Juego->JugadorActual = 'B';
        Juego->Oponente = 'W';
    }
    else {
        Juego->JugadorActual = 'W';
        Juego->Oponente = 'B';
    }
}

COORD ObtenerCoordenadas(GAME Juego,int size){
    COORD coordenada;
    int x, y;
    COORD puntos = Puntos(Juego,size);
    printf("El jugador B tiene: %d Puntos\n", puntos.x);
    printf("El jugador W tiene: %d Puntos\n", puntos.y);
    printf("\n");
    printf("Es el turno de: %c", Juego.JugadorActual);
    printf("\n");
    while(1) {
        while (1) {
            //Se pide que sean números dentro del tablero
            printf("\nIngrese cordenadas de una jugada posible x, y\n");
            scanf("%d, %d", &x, &y);
            if (x >= 0 && x < size && y >= 0 && y < size) {
                break;
            }
        }
        //Si esta dentro del tablero, debe ser una A sino no es valido
        if (Juego.tablero[y][x] == 'A') {
            break;
        }
    }
    coordenada.x = x;
    coordenada.y = y;
    return coordenada;
}

int EndGame(GAME Juego, int size){
    //El juego termina si: No hay más espacios o si ningun jugador tiene movimientos posibles
    int CasillasLibres = 0;
    for (int y = 0; y < size; y++){
        for (int x = 0; x < size; x++){
            if(Juego.tablero[y][x] == '0'){
                CasillasLibres++;
            }
        }
    }
    int JugadasTurnoActual = MovimientosDisponibles(&Juego, size);
    Juego.turno++;
    LimpiarTablero(&Juego, size);
    int  JugadasTurnoSiguiente = MovimientosDisponibles(&Juego, size);
    LimpiarTablero(&Juego, size);
    return (CasillasLibres && (JugadasTurnoActual || JugadasTurnoSiguiente));
}

COORD Puntos(GAME Juego,int size){
    //Recorrer el tablero contando fichas de ambos colores
    COORD Puntos;
    int CantidadB = 0;
    int CantidadW = 0;
    for(int y = 0; y < size; y++){
        for(int x = 0; x < size; x++){
            if(Juego.tablero[y][x] == 'W'){
                CantidadW++;
            }
            if(Juego.tablero[y][x] == 'B'){
                CantidadB++;
            }
        }
    }
    Puntos.x = CantidadB;
    Puntos.y = CantidadW;
    return Puntos;
}