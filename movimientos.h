#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H

#include "GBT/gbt_temporizador.h"
#include "GBT/gbt_entrada.h"
#include "GBT/gbt.h"
#include "tablero.h"
#include "juego.h"
#include "tetromino.h"
#include "pantalla.h"

#define MINO_PIVOTE 2

void mover_derecha(const t_tablero *tablero, t_tetromino *tetromino);
void mover_izquierda(const t_tablero *tablero, t_tetromino *tetromino);
bool girar(const t_tablero *tablero, t_tetromino *tetromino);
int temporizador_movimientos_caida(t_tablero *tablero, t_tetromino *tetromino, double tiempo_caida);
int temporizador_movimientos_tolerancia(t_tablero *tablero, t_tetromino *tetromino, double tiempo_tolerancia);


#endif
