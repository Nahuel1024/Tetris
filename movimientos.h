/**
 * @file movimientos.h
 * @brief Movimientos laterales, rotacion y temporizadores de caida/tolerancia.
 * @version 1.1
 */

#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H

#include "GBT/gbt_temporizador.h"
#include "GBT/gbt_entrada.h"
#include "GBT/gbt.h"
#include "tablero.h"
#include "tetromino.h"
#include "layout.h"
#include "pagina_juego.h"

#define MINO_PIVOTE 2

void mover_derecha(const t_tablero *tablero, t_tetromino *tetromino);
void mover_izquierda(const t_tablero *tablero, t_tetromino *tetromino);
bool girar(const t_tablero *tablero, t_tetromino *tetromino);

/**
 * @brief Temporizador de caida: procesa entrada lateral/rotacion durante el descenso.
 *
 * @param layout    Layout activo, necesario para redibujar solo tablero y pieza.
 * @param siguiente Tetromino siguiente, necesario para la pausa.
 */
int temporizador_movimientos_caida(const t_layout *layout,
                                    t_tablero *tablero,
                                    t_tetromino *tetromino,
                                    const t_tetromino *siguiente,
                                    double tiempo_caida);

/**
 * @brief Temporizador de tolerancia (lock delay): permite mover antes de fijar.
 *
 * @param layout    Layout activo, necesario para redibujar solo tablero y pieza.
 * @param siguiente Tetromino siguiente, necesario para la pausa.
 */
int temporizador_movimientos_tolerancia(const t_layout *layout,
                                         t_tablero *tablero,
                                         t_tetromino *tetromino,
                                         const t_tetromino *siguiente,
                                         double tiempo_tolerancia);

#endif
