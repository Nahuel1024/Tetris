#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H

#include "GBT/gbt_temporizador.h"
#include "GBT/gbt_entrada.h"
#include "GBT/gbt.h"
#include "tablero.h"
#include "tetromino.h"
#include "pantalla.h"

#define MINO_PIVOTE 2

void mover_derecha(t_tetromino *tetromino);
void mover_izquierda(t_tetromino *tetromino);
bool girar(const t_tablero *tablero, t_tetromino *tetromino);
void temporizador_movimientos(t_tablero *tablero, t_tetromino *tetromino);

#endif
