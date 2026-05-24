/**
 * @file pantalla.h
 * @brief Capa de renderizado e interfaz grafica usando la libreria GBT.
 * @version 1.3
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

#define ANCHO_CGA       320     ///< Resolucion horizontal CGA
#define ALTO_CGA        200     ///< Resolucion vertical CGA
#define ANCHO_VGA       640     ///< Resolucion horizontal VGA
#define ALTO_VGA        480     ///< Resolucion vertical VGA

#define TAM_ESCALA      2       ///< Factor de escala fisica de la ventana (pixeles NxN)
#define FILAS_SPAWN     2       ///< Filas superiores reservadas para spawn (no visibles)

#define TAM_CELDA_BASE  10      ///< Tamanio base de celda en pixeles para CGA
#define TAM_CELDA       ((int)(TAM_CELDA_BASE * escala_pantalla))  ///< Tamanio real segun resolucion

/* ========================================================================== */
/* VARIABLES GLOBALES DE ESTADO VISUAL                                        */
/* ========================================================================== */

extern int    ancho_sistema;    ///< Ancho logico del canvas activo
extern int    alto_sistema;     ///< Alto logico del canvas activo
extern double escala_pantalla;  ///< Factor de escala del contenido (1.0=CGA, 1.5=VGA)
extern int    margen_y;         ///< Primer pixel Y visible (0 en CGA, 60 en VGA)
extern int    alto_visible;     ///< Alto del area realmente utilizable por los dibujos

/* ========================================================================== */
/* PROTOTIPOS DE FUNCIONES DE RENDERIZADO                                     */
/* ========================================================================== */

void iniciar_pantalla(int reso);
void dibujar(const t_tablero *var_tablero, const t_tetromino *tetromino);
void dibujar_tablero(const t_tablero *var_tablero, int ini_x, int ini_y);
void dibujar_pieza(const t_tetromino *tetromino, int ini_x, int ini_y);
void dibujar_rectangulo(int x, int y, int ancho, int alto, int color);
void dibujar_cuadrado(int x, int y, int color, int tam);

#endif // PANTALLA_H_INCLUDED
