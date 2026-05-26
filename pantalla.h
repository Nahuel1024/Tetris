/**
 * @file pantalla.h
 * @brief Capa de renderizado e interfaz grafica usando la libreria GBT.
 * @version 1.5
 */

#ifndef PANTALLA_H_INCLUDED
#define PANTALLA_H_INCLUDED

#include "GBT/gbt.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "comun.h"
#include "tablero.h"
#include "tetromino.h"
#include "paletacolor.h"

/* ========================================================================== */
/* CONSTANTES DE RESOLUCION Y PANTALLA                                        */
/* ========================================================================== */

#define ANCHO_CGA       320
#define ALTO_CGA        200
#define ANCHO_VGA       640
#define ALTO_VGA        480

#define TAM_ESCALA      2
#define FILAS_SPAWN     2

#define TAM_CELDA_BASE  10
#define TAM_CELDA       ((int)(TAM_CELDA_BASE * escala_pantalla))

/* ========================================================================== */
/* VARIABLES GLOBALES DE ESTADO VISUAL                                        */
/* ========================================================================== */

extern int    ancho_sistema;
extern int    alto_sistema;
extern double escala_pantalla;
extern int    margen_y;
extern int    alto_visible;

/* ========================================================================== */
/* PROTOTIPOS                                                                 */
/* ========================================================================== */

void iniciar_pantalla(int reso);

/**
 * @brief Orquestador principal de dibujo.
 *
 * @param var_tablero  Tablero con los bloques fijos.
 * @param tetromino    Pieza activa cayendo.
 * @param siguiente    Pieza siguiente para el preview del HUD.
 */
void dibujar(const t_tablero *var_tablero, const t_tetromino *tetromino,
             const t_tetromino *siguiente);

void dibujar_tablero(const t_tablero *var_tablero, int ini_x, int ini_y);
void dibujar_pieza(const t_tetromino *tetromino, int ini_x, int ini_y);
void dibujar_rectangulo(int x, int y, int ancho, int alto, int color);
void dibujar_cuadrado(int x, int y, int color, int tam);
void dibujar_cartel_pausa(void);

#endif // PANTALLA_H_INCLUDED
