/**
 * @file juego.h
 * @brief Orquestador principal de las reglas del juego y físicas.
 * @version 1.0
 */

#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#define FIN 1
#define OK 0

#include "comun.h"
#include "tetromino.h"
#include "tablero.h"
#include "movimientos.h"

/* ========================================================================== */
/* PROTOTIPOS DE FUNCIONES                                                    */
/* ========================================================================== */

/* --- Generación y Estado --- */

/**
 * @brief Genera una pieza aleatoria y la posiciona en el área de spawn.
 * @param tablero Puntero al entorno del juego para validar el espacio.
 * @param tetromino Puntero a la pieza que se va a inicializar.
 * @return true si la inserción fue exitosa, false si el área está ocupada (Game Over).
 */
bool tetromino_insertar(t_tablero *tablero, t_tetromino *tetromino);

/**
 * @brief Transfiere de forma permanente los 4 bloques de la pieza activa a la matriz estática.
 */
void tablero_actualizar(t_tablero *tablero, const t_tetromino *tetromino);

/**
 * @brief Función auxiliar que fija un mino individual en la matriz.
 */
void mino_fijar(t_tablero *tablero, const t_mino *mino);


/* --- Físicas y Colisiones --- */

/**
 * @brief Orquesta la caída general evaluando la física de todos los minos.
 * @return true si la pieza entera tiene espacio para seguir cayendo.
 */
bool tetromino_cayendo(const t_tablero *tablero, const t_tetromino *tetromino);

/**
 * @brief Detecta si un mino individual colisionó contra el límite inferior o un bloque fijo.
 */
bool mino_sobre_suelo(const t_tablero *tablero, const t_mino *mino);


/* --- Renderizado de Depuración --- */

/**
 * @brief Renderiza en la consola el estado actual de la matriz y la pieza en caída.
 */
void tablero_mostrar(const t_tablero *tablero, const t_tetromino *tetromino);

#endif // JUEGO_H_INCLUDED
