#include "movimientos.h"
#include "tetromino.h"
#include "comun.h"
#include "tablero.h"

void mover_derecha(t_tetromino *tetromino)
{
    for (int i = 0; i < CANTIDAD_MINOS; i++)
    {
        if (tetromino->mino[i].coordenadas.columna + 1 >= CANTIDAD_COLUMNAS) //Verificamos si algun bloque dibujado del tetromino se sale de nuestro rango de tablero a la derecha
            return; //Si se sale, no realiza el movimiento
    }

    for (int i = 0; i < CANTIDAD_MINOS; i++) // Si el movimiento se puede realizar, desplaza todos los bloques una columna a la derecha
    {
        tetromino->mino[i].coordenadas.columna++;
    }
}

void mover_izquierda(t_tetromino *t) //Funciona de la misma forma pero ahora verifica con la COLUMNA = 0
{
    for (int i = 0; i < CANTIDAD_MINOS; i++)
    {
        if (t->mino[i].coordenadas.columna <= 0)
            return;
    }

    for (int i = 0; i < CANTIDAD_MINOS; i++)
    {
        t->mino[i].coordenadas.columna--;
    }
}
