#include "iaminimax.h"
#include "FuncionesReversi.h"

int minimax(GAME Copia, int niveles, bool maximiza, int tam){
    //se calcula un resultado (final)
    int resultado = EndGame(Copia, tam);
    //si ya es el final del juego
    if (resultado!=1){
        //se obtienen la puntuacion de ese tablero y se regresa como puntuacion
        int puntuacion = Puntos(Copia,tam).y;
        return puntuacion;
    }
    //si le toca a la IA
    if (maximiza){
        //se hace lo mismo, se calculan ahora los posibles movimientos y la mejor puntuacion
        //DEL PRIMER MOVIMIENTO QUE SE ESTA ANALIZANDO EN LA PRIMER LLAMADA A MINIMAX
        MovimientosDisponibles(&Copia,tam);
        int mejorpuntuacion = Puntos(Copia,tam).y;
        for (int y = 0; y < tam; y++) {
            for (int x = 0; x < tam; x++) {
                if (Copia.tablero[y][x] == 'A') {
                    RealizarMovimiento(&Copia,tam,x,y);
                    //se hace una recursividad a minimax con el nivel+1 pero ahora con el turno del humano
                    //esto para asumir que el humano hace la mejor movida
                    int puntuacion = minimax(Copia,niveles+1, false, tam);
                    Copia.turno--;
                    Copia.tablero[y][x]='A';
                    if (puntuacion > mejorpuntuacion) {
                        mejorpuntuacion = puntuacion;
                    }
                }
            }
        }
        //se regresa la mejor puntuacion
        LimpiarTablero(&Copia,tam);
        return mejorpuntuacion;
    }else{
        //aqui se simula el turno del usuario
        Copia.turno++;
        //se suma un turno para poder movernos con las negras
        MovimientosDisponibles(&Copia,tam);
        int mejorpuntuacion = Puntos(Copia,tam).x;
        for (int y = 0; y < tam; y++) {
            for (int x = 0; x < tam; x++) {
                if (Copia.tablero[y][x] == 'A') {
                    RealizarMovimiento(&Copia,tam,x,y);
                    //se hacen los movimientos y se calcula la mejor puntuacion
                    //se vuelve a llamar a minimax un nivel mas abajo, en este caso le toca de nuevo a la IA
                    //por eso se llama minimax pero con true
                    int puntuacion = minimax(Copia,niveles+1, true, tam);
                    Copia.turno--;
                    Copia.tablero[y][x]='A';
                    if (puntuacion > mejorpuntuacion) {
                        mejorpuntuacion = puntuacion;
                    }
                }
            }
        }
        //se regresa la mejor puntuación del usuario
        LimpiarTablero(&Copia,tam);
        return mejorpuntuacion;
    }
}
