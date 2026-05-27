/**
 * @file tetromino.h
 * @brief Motor de gesti�n de piezas activas (Tetrominos).
 * @version 1.3
 */

#ifndef TETROMINO_H_INCLUDED
#define TETROMINO_H_INCLUDED

#include "comun.h"
#include "tablero.h"
#include "GBT/gbt_vector.h"

/* ========================================================================== */
/* ESTRUCTURAS DE DATOS                                                       */
/* ========================================================================== */

/**
 * @brief Representa un bloque individual (componente de un tetromino).
 */
typedef struct {
    t_coordenadas coordenadas; ///< Posici�n f�sica en la matriz.
    unsigned color;            ///< �ndice de color seg�n la paleta.
} t_mino;

/**
 * @brief Estructura de la pieza activa controlada por el juego.
 */
typedef struct {
    t_mino mino[CANTIDAD_MINOS];
    char pieza;
} t_tetromino;

typedef struct {
    char pieza;
    int contador;
} t_contador_tetromino;

typedef struct {
    tGBT_Vector lista_tetrominos;
}
t_vector_tetrominos;

/* ========================================================================== */
/* PROTOTIPOS DE FUNCIONES                                                    */
/* ========================================================================== */

/* --- L�gica de Movimiento --- */

/**
 * @brief Desplaza un mino individual una fila hacia abajo.
 */
void mino_desplazar(t_mino *mino);

/**
 * @brief Aplica gravedad a los 4 minos del tetromino activo simult�neamente.
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
 * @brief Comprueba si una coordenada coincide con la posici�n de la pieza activa.
 */
bool es_mino(const t_coordenadas *celda, const t_tetromino *tetromino);

/* --- Vectores --- */

/**
 * @brief Crea el vector de contador de tetrominos.
 */
//void lista_tetrominos_inicializar(t_vector_tetrominos *lista);

/* ========================================================================== */
/* DATOS EXTERNOS                                                             */
/* ========================================================================== */

/**
 * @brief Matriz global que define la geometr�a de las 7 piezas cl�sicas.
 */
extern int tetrominos[7][4][4];

#endif // TETROMINO_H_INCLUDED
