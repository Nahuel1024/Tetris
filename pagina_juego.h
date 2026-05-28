/**
 * @file pagina_juego.h
 * @brief Renderizado completo de la pantalla principal de juego.
 * @version 1.1
 */

#ifndef PAGINA_JUEGO_H_INCLUDED
#define PAGINA_JUEGO_H_INCLUDED

#include "layout.h"
#include "primitivas.h"
#include "fuente.h"
#include "tablero.h"
#include "tetromino.h"

/* ========================================================================== */
/* ORQUESTADOR PRINCIPAL                                                      */
/* ========================================================================== */

/**
 * @brief Dibuja el frame completo de la pantalla de juego.
 *
 * @param layout    Layout activo con escala y margenes.
 * @param tablero   Tablero con los bloques fijos.
 * @param tetromino Pieza activa cayendo.
 * @param siguiente Pieza siguiente para el preview del HUD.
 * @param puntaje   Puntaje actual del jugador.
 */
void dibujar_juego(const t_layout *layout, const t_tablero *tablero,
                   const t_tetromino *tetromino, const t_tetromino *siguiente,
                   int puntaje);

/* ========================================================================== */
/* COMPONENTES INDIVIDUALES                                                   */
/* ========================================================================== */

void dibujar_fondo_juego(const t_layout *layout);
void dibujar_tablero(const t_layout *layout, const t_tablero *tablero);
void dibujar_pieza(const t_layout *layout, const t_tetromino *tetromino);

/**
 * @brief Dibuja los paneles laterales del HUD.
 *
 * @param layout    Layout activo.
 * @param siguiente Pieza siguiente para el preview.
 * @param puntaje   Puntaje actual del jugador (se muestra con 7 digitos y ceros a la izquierda).
 */
void dibujar_hud(const t_layout *layout, const t_tetromino *siguiente, int puntaje);

void dibujar_cartel_pausa(const t_layout *layout);

#endif // PAGINA_JUEGO_H_INCLUDED
