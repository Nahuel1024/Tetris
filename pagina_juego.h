/**
 * @file pagina_juego.h
 * @brief Renderizado completo de la pantalla principal de juego.
 *
 * Fusiona las responsabilidades de pantalla.c y pantallainicio.c:
 * tablero, pieza activa, HUD lateral y cartel de pausa.
 *
 * Todas las funciones reciben el layout por puntero para evitar
 * dependencia de variables globales.
 *
 * @version 1.0
 */

#ifndef PAGINA_JUEGO_H_INCLUDED
#define PAGINA_JUEGO_H_INCLUDED

#include "layout.h"
#include "primitivas.h"
#include "fuente.h"
#include "puntaje.h"
#include "tablero.h"
#include "tetromino.h"

/* ========================================================================== */
/* ORQUESTADOR PRINCIPAL                                                      */
/* ========================================================================== */

/**
 * @brief Dibuja el frame completo de la pantalla de juego.
 *
 * Llama en orden a: fondo, HUD, tablero fijo, pieza activa.
 * Incluye borrar y volcar el backbuffer.
 *
 * @param layout    Layout activo con escala y margenes.
 * @param tablero   Tablero con los bloques fijos.
 * @param tetromino Pieza activa cayendo.
 * @param siguiente Pieza siguiente para el preview del HUD.
 */
void dibujar_juego(const t_layout *layout, const t_tablero *tablero,const t_tetromino *tetromino, const t_tetromino *siguiente);
/* ========================================================================== */
/* COMPONENTES INDIVIDUALES (utiles para redibujos parciales en movimientos)  */
/* ========================================================================== */

/**
 * @brief Dibuja el fondo del area de juego.
 */
void dibujar_fondo_juego(const t_layout *layout);

/**
 * @brief Dibuja los bloques fijos del tablero.
 */
void dibujar_tablero(const t_layout *layout, const t_tablero *tablero);

/**
 * @brief Dibuja la pieza activa, ocultando minos en zona de spawn.
 */
void dibujar_pieza(const t_layout *layout, const t_tetromino *tetromino);

/**
 * @brief Dibuja los paneles laterales del HUD con puntaje y preview.
 */
void dibujar_hud(const t_layout *layout, const t_tetromino *siguiente);

/**
 * @brief Dibuja el cartel de pausa centrado en el area visible.
 *        Debe llamarse despues de dibujar_juego() y antes de gbt_volcar_backbuffer().
 */
void dibujar_cartel_pausa(const t_layout *layout);

void dibujar_cartel_game_over(const t_layout *layout);

#endif // PAGINA_JUEGO_H_INCLUDED
