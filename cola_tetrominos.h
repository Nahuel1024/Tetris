/**
 * @file cola_tetrominos.h
 * @brief TDA Cola de Tetrominos para gestionar la pieza activa y la siguiente.
 *
 * Mantiene exactamente 2 tetróminos en un vector:
 *   - Posicion 0: tetromino activo (cayendo actualmente)
 *   - Posicion 1: tetromino siguiente (se muestra en el HUD)
 *
 * Al fijar una pieza, el siguiente pasa a activo y se genera uno nuevo
 * en la posicion 1, garantizando que siempre haya preview disponible.
 *
 * Uso tipico:
 *   t_cola_tetrominos cola;
 *   cola_tetrominos_inicializar(&cola, &tablero);
 *
 *   // En el bucle principal:
 *   t_tetromino *actual = cola_tetrominos_actual(&cola);
 *   while(tetromino_cayendo(&tablero, actual)) { ... }
 *
 *   // Al fijar:
 *   tablero_actualizar(&tablero, actual);
 *   cola_tetrominos_avanzar(&cola, &tablero);
 *
 *   // Al destruir:
 *   cola_tetrominos_destruir(&cola);
 *
 * @version 1.0
 */

#ifndef COLA_TETROMINOS_H_INCLUDED
#define COLA_TETROMINOS_H_INCLUDED

#include "tetromino.h"
#include "tablero.h"
#include "GBT/gbt_vector.h"

#define COLA_CAPACIDAD 2  ///< Cantidad fija de tetróminos en la cola (actual + siguiente)

/* ========================================================================== */
/* TDA                                                                        */
/* ========================================================================== */

/**
 * @brief Cola de tetróminos de capacidad fija (2 elementos).
 */
typedef struct {
    tGBT_Vector vector;  ///< Vector interno de t_tetromino
} t_cola_tetrominos;

/* ========================================================================== */
/* PROTOTIPOS                                                                 */
/* ========================================================================== */

/**
 * @brief Inicializa la cola e inserta dos tetróminos aleatorios.
 *
 * El primero (posicion 0) se posiciona en el area de spawn del tablero.
 * El segundo (posicion 1) solo tiene forma y color, sin coordenadas de juego.
 *
 * @param cola    Cola a inicializar.
 * @param tablero Tablero activo, necesario para posicionar el tetromino actual.
 */
void cola_tetrominos_inicializar(t_cola_tetrominos *cola, t_tablero *tablero);

/**
 * @brief Devuelve un puntero al tetromino activo (posicion 0).
 *
 * @param cola  Cola inicializada.
 * @return      Puntero al t_tetromino activo.
 */
t_tetromino* cola_tetrominos_actual(t_cola_tetrominos *cola);

/**
 * @brief Devuelve un puntero al tetromino siguiente (posicion 1).
 *
 * @param cola  Cola inicializada.
 * @return      Puntero al t_tetromino siguiente.
 */
t_tetromino* cola_tetrominos_siguiente(t_cola_tetrominos *cola);

/**
 * @brief Desplaza la cola: el siguiente pasa a activo y genera uno nuevo en posicion 1.
 *
 * Debe llamarse despues de fijar el tetromino activo en el tablero.
 * El nuevo tetromino siguiente solo tiene forma y color (sin coordenadas de spawn).
 *
 * @param cola    Cola a avanzar.
 * @param tablero Tablero activo, necesario para posicionar el nuevo tetromino actual.
 * @return        true si el avance fue exitoso, false si el area de spawn esta ocupada (game over).
 */
bool cola_tetrominos_avanzar(t_cola_tetrominos *cola, t_tablero *tablero);

/**
 * @brief Libera la memoria del vector interno.
 *
 * @param cola  Cola a destruir.
 */
void cola_tetrominos_destruir(t_cola_tetrominos *cola);

#endif // COLA_TETROMINOS_H_INCLUDED
