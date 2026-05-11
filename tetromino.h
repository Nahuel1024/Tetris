/**
 * @file tetromino.h
 * @brief Motor de gestión de piezas activas (Tetrominos).
 * @version 1.3
 */

#ifndef TETROMINO_H_INCLUDED
#define TETROMINO_H_INCLUDED

#include "comun.h"
#include "tablero.h"

/* ========================================================================== */
/* ESTRUCTURAS DE DATOS                                                       */
/* ========================================================================== */

/**
 * @brief Representa un bloque individual (componente de un tetromino).
 */
typedef struct {
    t_coordenadas coordenadas; ///< Posición física en la matriz.
    unsigned color;            ///< Índice de color según la paleta.
} t_mino;

/**
 * @brief Estructura de la pieza activa controlada por el juego.
 */
typedef struct {
    t_mino mino[CANTIDAD_MINOS];
} t_tetromino;

/* ========================================================================== */
/* PROTOTIPOS DE FUNCIONES                                                    */
/* ========================================================================== */

/* --- Lógica de Movimiento --- */

/**
 * @brief Desplaza un mino individual una fila hacia abajo.
 */
void mino_desplazar(t_mino *mino);

/**
 * @brief Aplica gravedad a los 4 minos del tetromino activo simultáneamente.
 */
void tetromino_desplazar(t_tetromino *tetromino);

/* --- Consultas y Validaciones --- */

/**
 * @brief Determina si un mino se encuentra en las filas ocultas (0 o 1).
 */
bool mino_en_area_spawn(const t_mino *mino);

/**
 * @brief Verifica si alguna parte de la pieza activa sigue en la zona de spawn.
 */
bool tetromino_en_area_spawn(const t_tetromino *tetromino);

/**
 * @brief Comprueba si una coordenada coincide con la posición de la pieza activa.
 */
bool es_mino(const t_coordenadas *celda, const t_tetromino *tetromino);

/* ========================================================================== */
/* DATOS EXTERNOS                                                             */
/* ========================================================================== */

/**
 * @brief Matriz global que define la geometría de las 7 piezas clásicas.
 */
extern int tetrominos[7][4][4];

#endif // TETROMINO_H_INCLUDED
