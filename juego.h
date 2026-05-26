/**
 * @file juego.h
 * @brief Orquestador principal de las reglas del juego, fisicas e inicializacion.
 * @version 1.1
 */

#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include "comun.h"
#include "tetromino.h"
#include "tablero.h"
#include "movimientos.h"
#include "layout.h"
#include "paletacolor.h"

#define SUELO_DETECTADO 1000
#define FORZAR_DESCENSO 2000
#define SALIR           3000
#define CAIDA           4000
#define FIJADO          5000
#define PAUSA           6000
#define FIN             1
#define OK              0

/* ========================================================================== */
/* INICIALIZACION DE PANTALLA                                                 */
/* ========================================================================== */

/**
 * @brief Inicializa la ventana grafica y devuelve el layout calculado.
 *
 * Crea la ventana segun la resolucion elegida, aplica la paleta de colores
 * y calcula el layout a partir del tablero recibido.
 *
 * @param reso     0 = CGA, cualquier otro valor = VGA.
 * @param tablero  Tablero activo, necesario para calcular margenes de centrado.
 * @return         Layout completamente inicializado listo para usar.
 */
void iniciar_pantalla(t_layout * layout, int reso, const t_tablero *tablero);

/* ========================================================================== */
/* GENERACION Y ESTADO                                                        */
/* ========================================================================== */

/**
 * @brief Genera una pieza aleatoria y la posiciona en el area de spawn.
 * @return true si la insercion fue exitosa, false si el area esta ocupada (Game Over).
 */
bool tetromino_insertar(t_tablero *tablero, t_tetromino *tetromino);

/**
 * @brief Transfiere los 4 bloques de la pieza activa a la matriz estatica.
 */
void tablero_actualizar(t_tablero *tablero, const t_tetromino *tetromino);

/**
 * @brief Fija un mino individual en la matriz.
 */
void mino_fijar(t_tablero *tablero, const t_mino *mino);

/* ========================================================================== */
/* FISICAS Y COLISIONES                                                       */
/* ========================================================================== */

/**
 * @brief Devuelve true si la pieza entera tiene espacio para seguir cayendo.
 */
bool tetromino_cayendo(const t_tablero *tablero, const t_tetromino *tetromino);

/**
 * @brief Detecta si un mino colisiono contra el limite inferior o un bloque fijo.
 */
bool mino_sobre_suelo(const t_tablero *tablero, const t_mino *mino);

/* ========================================================================== */
/* RENDERIZADO DE DEPURACION                                                  */
/* ========================================================================== */

/**
 * @brief Renderiza en consola el estado actual del tablero y la pieza.
 */
void tablero_mostrar(const t_tablero *tablero, const t_tetromino *tetromino);

#endif // JUEGO_H_INCLUDED
