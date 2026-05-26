/**
 * @file primitivas.h
 * @brief Operaciones graficas base: rectangulos y cuadrados con efecto 3D.
 *
 * Estas funciones no conocen el contexto del juego. Reciben el layout
 * unicamente para obtener la escala y aplicar proporciones correctas.
 *
 * @version 1.0
 */

#ifndef PRIMITIVAS_H_INCLUDED
#define PRIMITIVAS_H_INCLUDED

#include "GBT/gbt.h"
#include "layout.h"
#include "paletacolor.h"

/* ========================================================================== */
/* PROTOTIPOS                                                                 */
/* ========================================================================== */

/**
 * @brief Dibuja un rectangulo solido pixel a pixel.
 *
 * @param layout  Layout activo (usado para escala futura si fuera necesario).
 * @param x       Coordenada X superior-izquierda.
 * @param y       Coordenada Y superior-izquierda.
 * @param ancho   Ancho en pixels.
 * @param alto    Alto en pixels.
 * @param color   Indice de color de la paleta global.
 */
void dibujar_rectangulo(const t_layout *layout, int x, int y, int ancho, int alto, int color);

/**
 * @brief Dibuja un cuadrado con efecto 3D de iluminacion superior-izquierda.
 *
 * El borde claro (superior e izquierdo) usa el color FONDO de la paleta.
 * El borde oscuro (inferior y derecho) usa el color BORDE de la paleta.
 * El grosor del borde es proporcional a la escala: 1px en CGA, 2px en VGA.
 *
 * @param layout  Layout activo, necesario para calcular el grosor del borde.
 * @param x       Coordenada X superior-izquierda.
 * @param y       Coordenada Y superior-izquierda.
 * @param color   Color del relleno interior.
 * @param tam     Tamanio del lado en pixels.
 */
void dibujar_cuadrado_3d(const t_layout *layout, int x, int y, int color, int tam);

#endif // PRIMITIVAS_H_INCLUDED
