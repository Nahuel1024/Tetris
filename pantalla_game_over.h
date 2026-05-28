/**
 * @file pantalla_game_over.h
 * @brief Pantalla de fin de juego con nombre, puntaje final y opciones de navegacion.
 *
 * @version 1.1
 */

#ifndef PANTALLA_GAME_OVER_H_INCLUDED
#define PANTALLA_GAME_OVER_H_INCLUDED

#include "layout.h"
#include "fuente.h"
#include "primitivas.h"
#include "paletacolor.h"
#include "GBT/gbt.h"

#define GAME_OVER_MENU          1
#define GAME_OVER_SALIR         2

#define GAME_OVER_OPC_MENU      1
#define GAME_OVER_OPC_SALIR     2
#define GAME_OVER_CANT_OPCIONES 2

#define GAME_OVER_BOTON_ANCHO_BASE  50
#define GAME_OVER_BOTON_ALTO_BASE   10
#define GAME_OVER_BOTON_SEP_BASE    10

#define GAME_OVER_COLOR_FONDO           BORDE
#define GAME_OVER_COLOR_TITULO          13
#define GAME_OVER_COLOR_NOMBRE          15  ///< Reservado: no usar en gbt_dibujar_pixel
#define GAME_OVER_COLOR_PUNTAJE         O
#define GAME_OVER_COLOR_BOTON_NORMAL    INTERFAZ
#define GAME_OVER_COLOR_BOTON_ACTIVO    J
#define GAME_OVER_COLOR_BOTON_TEXTO     14

/**
 * @brief Dibuja el frame completo de la pantalla de game over.
 *
 * @param layout   Layout activo.
 * @param nombre   Nombre del jugador.
 * @param puntaje  Puntaje final.
 * @param cursor   Opcion seleccionada (GAME_OVER_OPC_*).
 */
void pantalla_game_over_dibujar(const t_layout *layout,
                                 const char *nombre, int puntaje, int cursor);

/**
 * @brief Ejecuta el loop completo de la pantalla de game over.
 *
 * @param layout   Layout activo.
 * @param nombre   Nombre del jugador.
 * @param puntaje  Puntaje final.
 * @return         GAME_OVER_MENU o GAME_OVER_SALIR.
 */
int pantalla_game_over_ejecutar(const t_layout *layout,
                                 const char *nombre, int puntaje);

#endif // PANTALLA_GAME_OVER_H_INCLUDED
