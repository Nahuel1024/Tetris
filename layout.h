/**
 * @file layout.h
 * @brief TDA Layout: agrupa las dimensiones y escala de la pantalla activa.
 *
 * Se calcula una unica vez luego de iniciar_pantalla() y se pasa por
 * puntero a todas las funciones de dibujo, eliminando la dependencia
 * de variables globales en los modulos de renderizado.
 *
 * Uso tipico (en main):
 *   iniciar_pantalla(RESO);
 *   t_layout layout = layout_calcular(&tablero);
 *
 *   dibujar_juego(&layout, &tablero, actual, siguiente);
 *
 * @version 1.0
 */

#ifndef LAYOUT_H_INCLUDED
#define LAYOUT_H_INCLUDED

#include "tablero.h"

/* ========================================================================== */
/* CONSTANTES DE RESOLUCION                                                   */
/* ========================================================================== */

#define ANCHO_CGA       320
#define ALTO_CGA        200
#define ANCHO_VGA       640
#define ALTO_VGA        480
#define TAM_ESCALA      2
#define FILAS_SPAWN     2
#define TAM_CELDA_BASE  10

/* ========================================================================== */
/* TDA                                                                        */
/* ========================================================================== */

/**
 * @brief Dimensiones, escala y margenes de la pantalla activa.
 *
 * Todos los valores se calculan en layout_calcular() a partir de la
 * resolucion elegida y las dimensiones del tablero.
 */
typedef struct {
    int    ancho_sistema;       ///< Ancho logico del canvas activo
    int    alto_sistema;        ///< Alto logico del canvas activo
    double escala_pantalla;     ///< Factor de escala (1.0=CGA, 1.5=VGA)
    int    margen_y;            ///< Primer pixel Y visible (0=CGA, 60=VGA)
    int    alto_visible;        ///< Alto del area utilizable por los dibujos
    int    margen_horizontal;   ///< X donde empieza el tablero
    int    margen_vertical;     ///< Y donde empieza el tablero (dentro del area visible)
    int    ancho_tablero;       ///< Ancho del tablero en pixels
    int    tam_celda;           ///< Tamanio real de celda en pixels (base * escala)
} t_layout;

/* ========================================================================== */
/* PROTOTIPOS                                                                  */
/* ========================================================================== */

/**
 * @brief Calcula el layout completo a partir del estado de pantalla y el tablero.
 *
 * Debe llamarse despues de iniciar_pantalla() y cada vez que cambie la
 * resolucion. El resultado es valido para toda la sesion de juego.
 *
 * @param (out) layout  Puntero al layout a inicializar.
 * @param ancho_sis     Ancho logico del canvas (de iniciar_pantalla).
 * @param alto_sis      Alto logico del canvas (de iniciar_pantalla).
 * @param escala        Factor de escala activo (de iniciar_pantalla).
 * @param margen        Margen Y visible (de iniciar_pantalla).
 * @param tablero       Tablero activo, necesario para calcular margenes de centrado.
 */
void layout_calcular(t_layout *layout,  int ancho_sis, int alto_sis, double escala,
                          int margen, const t_tablero *tablero);

#endif // LAYOUT_H_INCLUDED
