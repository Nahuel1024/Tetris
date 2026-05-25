/**
 * @file nombre.h
 * @brief Pantalla de ingreso de nombre de usuario mediante teclado en pantalla.
 *
 * Permite al jugador componer un nombre de exactamente 3 caracteres navegando
 * un teclado QWERTY renderizado con primitivas pixel a pixel.
 * No depende de funciones de texto de la libreria GBT: cada glifo se dibuja
 * con una fuente bitmap 5x7 definida internamente.
 *
 * Uso tipico (desde main):
 *   char nombre[NOMBRE_MAX_CHARS + 1];
 *   pedir_nombre(nombre);
 *   // nombre contiene exactamente 3 letras mayusculas + '\0'
 *
 * @version 1.1
 */

#ifndef NOMBRE_H_INCLUDED
#define NOMBRE_H_INCLUDED

#include "GBT/gbt.h"
#include <stdbool.h>
#include <string.h>

#include "pantalla.h"       ///< dibujar_rectangulo(), ancho_sistema, alto_sistema, escala_pantalla
#include "paletacolor.h"    ///< Indices de color compartidos con el resto del juego

/* ========================================================================== */
/* CONSTANTES PROPIAS DEL MODULO                                              */
/* ========================================================================== */

/** Cantidad de caracteres que componen el nombre del jugador. */
#define NOMBRE_MAX_CHARS    3

/** Filas y columnas del teclado en pantalla (layout QWERTY). */
#define TECLADO_FILAS       3
#define TECLADO_COLS        10

/**
 * Tamanio base en pixeles de cada tecla para resolucion CGA.
 * El tamanio real se obtiene multiplicando por escala_pantalla.
 */
#define TAM_TECLA           18

/** Separacion base en pixeles entre teclas para resolucion CGA. */
#define SEP_TECLA           2

/* ========================================================================== */
/* ESTRUCTURA INTERNA DE ESTADO                                               */
/* ========================================================================== */

/**
 * @brief Estado completo de la pantalla de ingreso de nombre.
 *
 * Agrupa el buffer del nombre en construccion, la posicion del cursor
 * sobre el teclado y cuantas letras se ingresaron hasta el momento.
 *
 * El cursor puede estar en:
 *  - Fila 0 a TECLADO_FILAS-1: sobre el teclado QWERTY
 *  - Fila TECLADO_FILAS: sobre el boton ACEPTAR (fila virtual)
 */
typedef struct {
    char    buffer[NOMBRE_MAX_CHARS + 1]; ///< Nombre en construccion (+ '\0')
    int     cursor_fila;                  ///< Fila activa en el teclado (0 a TECLADO_FILAS)
    int     cursor_col;                   ///< Columna activa en el teclado (0 a TECLADO_COLS-1)
    int     cantidad_letras;              ///< Caracteres ingresados hasta ahora (0 a NOMBRE_MAX_CHARS)
} t_estado_nombre;

/* ========================================================================== */
/* PROTOTIPOS PUBLICOS                                                        */
/* ========================================================================== */

/* --- Gestion de estado --- */

/**
 * @brief Inicializa el estado de ingreso de nombre con valores por defecto.
 *
 * Vacia el buffer, posiciona el cursor en la tecla Q (fila 0, columna 0)
 * y pone la cantidad de letras en 0.
 *
 * @param[out] estado  Puntero al estado a inicializar.
 */
void t_estado_nombre_inicializiar(t_estado_nombre *estado);

/**
 * @brief Indica si el nombre ingresado esta completo.
 *
 * @param estado  Estado actual de la pantalla de ingreso.
 * @return true   Si cantidad_letras == NOMBRE_MAX_CHARS.
 * @return false  Si aun faltan letras por ingresar.
 */
bool t_estado_nombre_completo(const t_estado_nombre *estado);

/* --- Punto de entrada principal --- */

/**
 * @brief Muestra la pantalla de ingreso de nombre y bloquea hasta que el
 *        usuario complete exactamente NOMBRE_MAX_CHARS letras y confirme
 *        con el boton ACEPTAR.
 *
 * El ingreso se realiza navegando un teclado QWERTY en pantalla con las
 * teclas de flecha y confirmando cada letra con Enter. La fila inferior
 * del teclado incluye un boton BORRAR que elimina la ultima letra ingresada.
 *
 * @param[out] nombre_destino  Buffer donde se copia el nombre resultante.
 *                             Debe tener al menos NOMBRE_MAX_CHARS + 1 bytes.
 */
void pedir_nombre(char *nombre_destino);

/* --- Renderizado: orquestador --- */

/**
 * @brief Dibuja el frame completo de la pantalla de ingreso.
 *
 * Llama en orden a: dibujar_fondo_nombre(), dibujar_display_nombre(),
 * dibujar_letras_display(), dibujar_teclado(), dibujar_boton_aceptar().
 * Vuelca el backbuffer al finalizar.
 *
 * @param estado  Estado actual (posicion del cursor y letras ingresadas).
 */
void dibujar_pantalla_nombre(const t_estado_nombre *estado);

/* --- Renderizado: componentes individuales --- */

/**
 * @brief Dibuja el fondo de la pantalla de ingreso y el titulo centrado.
 *
 * El fondo cubre unicamente el area visible (entre margen_y y alto_visible).
 */
void dibujar_fondo_nombre(void);

/**
 * @brief Dibuja el display donde se muestran las letras ingresadas.
 *
 * El display tiene un marco perimetral y se divide en NOMBRE_MAX_CHARS slots,
 * separados por bordes internos verticales. Los bordes se dibujan pintando
 * primero el marco completo y luego rellenando cada slot individualmente,
 * dejando los bordes visibles de forma automatica.
 *
 * @param estado  Estado actual (reservado para variaciones visuales futuras).
 */
void dibujar_display_nombre(const t_estado_nombre *estado);

/**
 * @brief Dibuja las letras ya ingresadas dentro de sus slots del display.
 *
 * Cada letra se centra dentro de su slot. Si el nombre no esta completo,
 * dibuja ademas un subrayado en el slot activo como indicador de posicion.
 *
 * @param estado  Estado actual con el buffer de nombre y cantidad de letras.
 */
void dibujar_letras_display(const t_estado_nombre *estado);

/**
 * @brief Dibuja el teclado QWERTY completo.
 *
 * Layout de 3 filas:
 *  - Fila 0: Q a P (10 teclas)
 *  - Fila 1: A a L (9 teclas, sangria de media tecla)
 *  - Fila 2: Z a M (7 teclas) + boton BORRAR (ancho de 3 teclas)
 *
 * La tecla bajo el cursor se resalta con COLOR_TECLA_CURSOR.
 * El boton BORRAR se resalta con COLOR_BOTON_ACTIVO y muestra una flecha
 * hacia la izquierda en lugar de un caracter.
 *
 * @param estado  Estado actual con la posicion del cursor.
 */
void dibujar_teclado(const t_estado_nombre *estado);

/**
 * @brief Dibuja el boton ACEPTAR en la parte inferior del area visible.
 *
 * El boton solo es funcional cuando el nombre esta completo (NOMBRE_MAX_CHARS
 * letras ingresadas). Se resalta con COLOR_BOTON_ACTIVO cuando el cursor
 * esta posicionado sobre el (cursor_fila == TECLADO_FILAS).
 *
 * @param activo  true si el cursor esta sobre el boton.
 */
void dibujar_boton_aceptar(bool activo);

/* --- Primitiva de texto bitmap --- */

/**
 * @brief Dibuja un caracter ASCII mayuscula usando una fuente bitmap 5x7.
 *
 * Cada pixel logico de la fuente se dibuja como un bloque de
 * escala_pantalla x escala_pantalla pixeles fisicos, para mantener
 * la legibilidad en resoluciones mayores a CGA.
 *
 * @param x      Coordenada X del pixel superior-izquierdo del glifo.
 * @param y      Coordenada Y del pixel superior-izquierdo del glifo.
 * @param c      Caracter a dibujar (solo acepta 'A'-'Z').
 * @param color  Indice de color de la paleta global.
 */
void dibujar_caracter(int x, int y, char c, int color);

#endif // NOMBRE_H_INCLUDED
