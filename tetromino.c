/**
 * @file tetromino.c
 * @brief Implementación de la lógica y geometría de los tetrominos.
 */

#include "tetromino.h"

/* ========================================================================== */
/* VECTOR GLOBAL DE TETROMINOS                                                */
/* ========================================================================== */

/**
 * COMPLEJO: Matriz Tridimensional de Formas
 * - El primer índice [7] representa el tipo de pieza (I, O, T, S, L, J, Z).
 * - Los siguientes [4][4] definen la grilla de rotación de la pieza.
 * * Los números (0-6) dentro de las matrices coinciden con los índices de
 * color de la paleta. El número 7 se utiliza como "vacío" o transparencia.
 */
int tetrominos[7][4][4] = {
    /* Pieza 0: I, 1: O, 2: T, 3: S, 4: L, 5: J, 6: Z */
    { {7,7,7,7},{0,0,0,0},{7,7,7,7},{7,7,7,7} },
    { {7,1,1,7},{7,1,1,7},{7,7,7,7},{7,7,7,7} },
    { {7,2,7,7},{2,2,2,7},{7,7,7,7},{7,7,7,7} },
    { {7,3,3,7},{3,3,7,7},{7,7,7,7},{7,7,7,7} },
    { {7,7,4,7},{4,4,4,7},{7,7,7,7},{7,7,7,7} },
    { {5,7,7,7},{5,5,5,7},{7,7,7,7},{7,7,7,7} },
    { {6,6,7,7},{7,6,6,7},{7,7,7,7},{7,7,7,7} }
};

/* ========================================================================== */
/* SECCIÓN: UTILIDADES DE ÁREA                                                */
/* ========================================================================== */

bool mino_en_area_spawn(const t_mino *mino)
{
    return (mino->coordenadas.fila == 0 || mino->coordenadas.fila == 1);
}

bool tetromino_en_area_spawn(const t_tetromino *tetromino)
{
    return (mino_en_area_spawn(&tetromino->mino[0]) ||
            mino_en_area_spawn(&tetromino->mino[1]) ||
            mino_en_area_spawn(&tetromino->mino[2]) ||
            mino_en_area_spawn(&tetromino->mino[3]));
}

bool es_mino(const t_coordenadas *celda, const t_tetromino *tetromino)
{
    return (celda->fila == tetromino->mino[0].coordenadas.fila && celda->columna == tetromino->mino[0].coordenadas.columna) ||
           (celda->fila == tetromino->mino[1].coordenadas.fila && celda->columna == tetromino->mino[1].coordenadas.columna) ||
           (celda->fila == tetromino->mino[2].coordenadas.fila && celda->columna == tetromino->mino[2].coordenadas.columna) ||
           (celda->fila == tetromino->mino[3].coordenadas.fila && celda->columna == tetromino->mino[3].coordenadas.columna);
}

/* ========================================================================== */
/* SECCIÓN: MOVIMIENTO                                                        */
/* ========================================================================== */

void mino_desplazar(t_mino *mino)
{
    mino->coordenadas.fila++;
}

void tetromino_desplazar(t_tetromino *tetromino)
{
    for(int i = 0; i < CANTIDAD_MINOS; i++)
    {
        mino_desplazar(&tetromino->mino[i]);
    }
}
