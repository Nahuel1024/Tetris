/**
 * @file fuente.h
 * @brief Sistema unificado de fuentes bitmap para renderizado de texto.
 *
 * Todas las funciones de dibujo reciben el layout para obtener la escala
 * activa, eliminando la dependencia de variables globales.
 *
 * @version 1.1
 */

#ifndef FUENTE_H_INCLUDED
#define FUENTE_H_INCLUDED

#include <stdint.h>
#include "GBT/gbt.h"
#include "layout.h"

/* ========================================================================== */
/* TDA: GLIFO Y FUENTE                                                        */
/* ========================================================================== */

typedef struct {
    char           caracter;
    const uint8_t *bitmap;
} t_glifo;

typedef struct {
    const char    *nombre;
    int            ancho;
    int            alto;
    int            espaciado;   ///< Espaciado base en pixels para CGA (escala 1.0)
    const t_glifo *glifos;
    int            cantidad;
} t_fuente;

/* ========================================================================== */
/* FUENTES DISPONIBLES                                                        */
/* ========================================================================== */

extern const t_fuente FUENTE_LARGE; ///< 8x8, letras parciales A-Z y digitos 0-9
extern const t_fuente FUENTE_SMALL; ///< 5x7, alfabeto A-Z completo

/* ========================================================================== */
/* PRIMITIVAS DE DIBUJO                                                       */
/* ========================================================================== */

/**
 * @brief Dibuja un caracter con la fuente y escala indicadas.
 *
 * Cada pixel logico se dibuja como un bloque de
 * (int)layout->escala_pantalla x (int)layout->escala_pantalla pixels fisicos.
 *
 * @param fuente  Fuente a usar.
 * @param layout  Layout activo, necesario para obtener la escala.
 * @param x       X del pixel superior-izquierdo del glifo.
 * @param y       Y del pixel superior-izquierdo del glifo.
 * @param c       Caracter a dibujar (solo 'A'-'Z' segun fuente).
 * @param color   Indice de color de la paleta global.
 */
void fuente_dibujar_caracter(const t_fuente *fuente, const t_layout *layout,
                              int x, int y, char c, int color);

/**
 * @brief Dibuja una cadena con la fuente y escala indicadas.
 *
 * @param fuente  Fuente a usar.
 * @param layout  Layout activo, necesario para obtener la escala.
 * @param x       X inicial del texto.
 * @param y       Y inicial del texto.
 * @param texto   Cadena terminada en '\0'.
 * @param color   Indice de color de la paleta global.
 */
void fuente_dibujar_texto(const t_fuente *fuente, const t_layout *layout,
                           int x, int y, const char *texto, int color);

/**
 * @brief Calcula el ancho en pixels fisicos de un texto con la fuente dada.
 *
 * @param fuente  Fuente a usar.
 * @param layout  Layout activo, necesario para obtener la escala.
 * @param texto   Cadena cuyo ancho se quiere calcular.
 * @return        Ancho total en pixels fisicos.
 */
int fuente_ancho_texto(const t_fuente *fuente, const t_layout *layout, const char *texto);

/**
 * @brief Calcula el alto en pixels fisicos de un glifo de la fuente dada.
 *
 * @param fuente  Fuente a usar.
 * @param layout  Layout activo, necesario para obtener la escala.
 * @return        Alto del glifo en pixels fisicos.
 */
int fuente_alto_glifo(const t_fuente *fuente, const t_layout *layout);

#endif // FUENTE_H_INCLUDED
