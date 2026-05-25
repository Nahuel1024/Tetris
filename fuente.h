/**
 * @file fuente.h
 * @brief Sistema unificado de fuentes bitmap para renderizado de texto.
 *
 * Provee un TDA estatico para representar fuentes de distintos tamanios
 * y funciones primitivas para dibujar caracteres y cadenas escalados
 * segun la resolucion activa (escala_pantalla de pantalla.h).
 *
 * Uso tipico:
 *   fuente_dibujar_texto(&FUENTE_LARGE, x, y, "PUNTOS", COLOR_TITULO);
 *   fuente_dibujar_texto(&FUENTE_SMALL, x, y, "INGRESE SU NOMBRE", COLOR_TITULO);
 *
 * Para agregar una fuente nueva:
 *   1. Definir los bitmaps en fuente.c
 *   2. Armar el array de t_glifo
 *   3. Definir la t_fuente y declararla como extern aqui
 *
 * @version 1.0
 */

#ifndef FUENTE_H_INCLUDED
#define FUENTE_H_INCLUDED

#include <stdint.h>
#include "GBT/gbt.h"
#include "pantalla.h"   ///< escala_pantalla

/* ========================================================================== */
/* TDA: GLIFO Y FUENTE                                                        */
/* ========================================================================== */

/**
 * @brief Asociacion entre un caracter y su bitmap.
 *
 * El bitmap es un array de 'alto' bytes donde cada byte representa
 * una fila de 'ancho' bits. El bit mas significativo es el pixel izquierdo.
 * Por ejemplo, para una fuente 8x8, bitmap[0] = 0x3C = 00111100
 * representa la primera fila con los pixeles 2 a 5 encendidos.
 */
typedef struct {
    char           caracter;  ///< Caracter ASCII que representa este glifo
    const uint8_t *bitmap;    ///< Array estatico de 'alto' bytes con el dibujo
} t_glifo;

/**
 * @brief Fuente bitmap con sus dimensiones y coleccion de glifos.
 *
 * Todas las dimensiones son en pixels logicos para CGA (escala 1.0).
 * El escalado a otras resoluciones lo aplica fuente_dibujar_caracter()
 * multiplicando por escala_pantalla.
 */
typedef struct {
    const char    *nombre;    ///< Identificador legible ("LARGE", "SMALL", etc.)
    int            ancho;     ///< Ancho base del glifo en pixels logicos
    int            alto;      ///< Alto base del glifo en pixels logicos
    int            espaciado; ///< Avance horizontal base entre caracteres (CGA)
    const t_glifo *glifos;   ///< Array estatico de glifos disponibles
    int            cantidad;  ///< Cantidad de glifos en el array
} t_fuente;

/* ========================================================================== */
/* FUENTES DISPONIBLES                                                        */
/* ========================================================================== */

/**
 * Fuente 8x8 de alta legibilidad.
 * Contiene: A C E G I M N O P R S T U X y digitos 0-9.
 * Espaciado base: 10px (CGA).
 */
extern const t_fuente FUENTE_LARGE;

/**
 * Fuente 5x7 compacta con alfabeto completo A-Z.
 * Espaciado base: 6px (CGA).
 */
extern const t_fuente FUENTE_SMALL;

/* ========================================================================== */
/* PRIMITIVAS DE DIBUJO                                                       */
/* ========================================================================== */

/**
 * @brief Dibuja un caracter con la fuente indicada.
 *
 * Cada pixel logico del bitmap se dibuja como un bloque de
 * (int)escala_pantalla x (int)escala_pantalla pixels fisicos,
 * manteniendo las proporciones en cualquier resolucion.
 * Si el caracter no existe en la fuente, no dibuja nada.
 *
 * @param fuente  Fuente a usar para el dibujo.
 * @param x       Coordenada X del pixel superior-izquierdo del glifo.
 * @param y       Coordenada Y del pixel superior-izquierdo del glifo.
 * @param c       Caracter a dibujar.
 * @param color   Indice de color de la paleta global.
 */
void fuente_dibujar_caracter(const t_fuente *fuente, int x, int y, char c, int color);

/**
 * @brief Dibuja una cadena de caracteres con la fuente indicada.
 *
 * Avanza horizontalmente fuente->espaciado * (int)escala_pantalla pixels
 * entre caracteres. Los caracteres no definidos en la fuente se saltean
 * avanzando el espaciado igual (comportamiento de espacio en blanco).
 *
 * @param fuente  Fuente a usar para el dibujo.
 * @param x       Coordenada X inicial del texto.
 * @param y       Coordenada Y inicial del texto.
 * @param texto   Cadena de caracteres a dibujar (terminada en '\0').
 * @param color   Indice de color de la paleta global.
 */
void fuente_dibujar_texto(const t_fuente *fuente, int x, int y, const char *texto, int color);

/**
 * @brief Calcula el ancho en pixels fisicos de un texto con la fuente dada.
 *
 * Util para centrar texto horizontalmente antes de dibujarlo:
 *   int x = panel_x + (panel_ancho - fuente_ancho_texto(&FUENTE_LARGE, "PUNTOS")) / 2;
 *
 * @param fuente  Fuente a usar para el calculo.
 * @param texto   Cadena cuyo ancho se quiere calcular.
 * @return        Ancho total en pixels fisicos (ya escalado).
 */
int fuente_ancho_texto(const t_fuente *fuente, const char *texto);

/**
 * @brief Calcula el alto en pixels fisicos de un glifo de la fuente dada.
 *
 * Util para centrar texto verticalmente dentro de un area:
 *   int y = panel_y + (panel_alto - fuente_alto_glifo(&FUENTE_LARGE)) / 2;
 *
 * @param fuente  Fuente a consultar.
 * @return        Alto del glifo en pixels fisicos (ya escalado).
 */
int fuente_alto_glifo(const t_fuente *fuente);

#endif // FUENTE_H_INCLUDED
