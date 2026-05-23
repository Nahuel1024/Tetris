/**
 * @file pantalla.h
 * @brief Capa de renderizado e interfaz gráfica usando la librería GBT.
 * @version 1.2
 */

#ifndef PANTALLA_H_INCLUDED
#define PANTALLA_H_INCLUDED

#include "GBT/gbt.h"
#include "GBT/gbt_graficos.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "comun.h"
#include "tablero.h"
#include "tetromino.h"
#include "paletacolor.h"

/* ========================================================================== */
/* CONSTANTES DE RESOLUCIÓN Y PANTALLA                                        */
/* ========================================================================== */

#define ANCHO_CGA 320   ///< Resolución horizontal CGA
#define ALTO_CGA 200    ///< Resolución vertical CGA
#define ANCHO_VGA 640   ///< Resolución horizontal VGA
#define ALTO_VGA 480    ///< Resolución vertical VGA

#define TAM_ESCALA 2    ///< Factor de escala para que no se vea minúsculo en monitores modernos
#define TAM_CELDA 10    ///< Tamaño en píxeles de cada bloque individual

/* ========================================================================== */
/* PROTOTIPOS DE FUNCIONES DE RENDERIZADO                                     */
/* ========================================================================== */

/* --- Control de Ventana --- */

/**
 * @brief Crea la ventana del juego según la resolución elegida (0 = CGA, otro = VGA).
 */
void iniciar_pantalla(int reso);

/* --- Orquestador Principal --- */

/**
 * @brief Función principal de dibujo: limpia la pantalla, dibuja fondo, tablero y pieza.
 */
void dibujar(const t_tablero *var_tablero, const t_tetromino *tetromino);

/* --- Componentes del Juego --- */

/**
 * @brief Recorre la matriz lógica del tablero y dibuja los bloques fijos.
 */
void dibujar_tablero(const t_tablero *var_tablero, int ini_x, int ini_y);

/**
 * @brief Dibuja la pieza que está cayendo actualmente en su posición correspondiente.
 */
void dibujar_pieza(const t_tetromino *tetromino, int ini_x, int ini_y);

/* --- Primitivas Gráficas --- */

/**
 * @brief Dibuja un rectángulo sólido píxel a píxel (usado para fondos).
 */
void dibujar_rectangulo(int x, int y, int ancho, int alto, int color);

/**
 * @brief Dibuja un cuadrado perfecto de tamaño 'tam' (usado para celdas/bloques).
 */
void dibujar_cuadrado(int x, int y, int color, int tam);

void dibujar_cartel_pausa();

#endif // PANTALLA_H_INCLUDED
