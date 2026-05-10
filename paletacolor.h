/**
 * @file paletacolor.h
 * @brief Definición de la paleta de colores del juego y mapeo de índices.
 * @version 1.1
 */

#ifndef PALETACOLOR_H_INCLUDED
#define PALETACOLOR_H_INCLUDED

#include "GBT/gbt_graficos.h"

/* ========================================================================== */
/* CONFIGURACIÓN GLOBAL DE PALETA                                             */
/* ========================================================================== */

#define CANT_COLORES 16 ///< Cantidad total de colores soportados por la paleta

/* ========================================================================== */
/* ÍNDICES DE COLOR PARA INTERFAZ Y ENTORNO                                   */
/* ========================================================================== */

#define BORDE    7 ///< Color base para el fondo del juego
#define INTERFAZ 8 ///< Color para la zona de juego visible o UI
#define FONDO    9 ///< Color para celdas ocupadas o bordes neutros

/* ========================================================================== */
/* ÍNDICES DE COLOR PARA TETROMINOS                                           */
/* ========================================================================== */
/* Nota: Estos valores coinciden estratégicamente con los números que
   componen las matrices de formas en tetromino.c */

#define I 0
#define O 1
#define T 2
#define S 3
#define L 4
#define J 5
#define Z 6

/* ========================================================================== */
/* VARIABLES EXTERNAS GLOBALES                                                */
/* ========================================================================== */

/**
 * @brief Arreglo global de colores RGB.
 * @note Se utiliza 'extern' para avisar al compilador que la variable existe,
 * pero su definición real de memoria se encuentra en paletacolor.c.
 */
extern tGBT_ColorRGB paleta[CANT_COLORES];

#endif // PALETACOLOR_H_INCLUDED
