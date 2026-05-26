#ifndef HUD_H
#define HUD_H

#include "tablero.h"
#include "tetromino.h"

/**
 * @brief Dibuja los paneles laterales del HUD.
 *
 * @param margen_horizontal  X donde empieza el tablero.
 * @param margen_vertical    Y donde empieza el tablero.
 * @param ancho_tablero      Ancho del tablero en pixels.
 * @param siguiente          Tetromino siguiente a mostrar en el preview.
 */
void dibujar_hud(int margen_horizontal, int margen_vertical,
                 int ancho_tablero, const t_tetromino *siguiente);

#endif
