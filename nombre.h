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
 * @version 1.0
 */

#ifndef NOMBRE_H_INCLUDED
#define NOMBRE_H_INCLUDED

#include "GBT/gbt.h"
#include <stdbool.h>
#include <string.h>

#include "pantalla.h"       ///< dibujar_rectangulo(), ancho_sistema, alto_sistema
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
 * Tamanio en pixeles de cada tecla del teclado en pantalla.
 * Debe caber en la resolucion CGA (320x200).
 */
#define TAM_TECLA           18

/** Separacion en pixeles entre teclas. */
#define SEP_TECLA           2

/** Escalas de los dibujos para la resolución elegida. */
#define TAM_TECLA_ACTUAL (TAM_TECLA * escala_pantalla)
#define SEP_TECLA_ACTUAL (SEP_TECLA * escala_pantalla)


/* ========================================================================== */
/* ESTRUCTURA INTERNA DE ESTADO (solo usada dentro del modulo)                */
/* ========================================================================== */

/**
 * @brief Estado completo de la pantalla de ingreso de nombre.
 *
 * Agrupa el buffer del nombre en construccion, la posicion del cursor
 * sobre el teclado y cuantas letras se ingresaron hasta el momento.
 */
typedef struct {
    char    buffer[NOMBRE_MAX_CHARS + 1]; ///< Nombre en construccion (+ '\0')
    int     cursor_fila;                  ///< Fila activa en el teclado (0-2)
    int     cursor_col;                   ///< Columna activa en el teclado (0-9)
    int     cantidad_letras;              ///< Caracteres ingresados hasta ahora
} t_estado_nombre;

/* ========================================================================== */
/* PROTOTIPOS PUBLICOS                                                        */
/* ========================================================================== */

/* --- Punto de entrada principal --- */

/**
 * @brief Muestra la pantalla de ingreso de nombre y espera a que el usuario
 *        complete exactamente NOMBRE_MAX_CHARS letras y presione Aceptar.
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
 */
void dibujar_pantalla_nombre(const t_estado_nombre *estado);

/* --- Renderizado: componentes individuales --- */

/**
 * @brief Dibuja el fondo de la pantalla de ingreso.
 */
void dibujar_fondo_nombre(void);

/**
 * @brief Dibuja el rectangulo donde se muestran las letras ingresadas.
 *
 * @param estado  Estado actual (para saber cuantas letras hay).
 */
void dibujar_display_nombre(const t_estado_nombre *estado);

/**
 * @brief Dibuja las letras ya ingresadas dentro del display.
 *
 * @param estado  Estado actual con el buffer de nombre.
 */
void dibujar_letras_display(const t_estado_nombre *estado);

/**
 * @brief Dibuja el teclado QWERTY completo, marcando la tecla bajo el cursor.
 *
 * @param estado  Estado actual con posicion del cursor.
 */
void dibujar_teclado(const t_estado_nombre *estado);

/**
 * @brief Dibuja el boton "ACEPTAR" en la parte inferior de la pantalla.
 *
 * @param activo  true si el cursor esta sobre el boton (se resalta).
 */
void dibujar_boton_aceptar(bool activo);

/* --- Primitiva de texto bitmap --- */

/**
 * @brief Dibuja un caracter ASCII mayuscula usando una fuente bitmap 5x7.
 *
 * @param x      Coordenada X del pixel superior-izquierdo del glifo.
 * @param y      Coordenada Y del pixel superior-izquierdo del glifo.
 * @param c      Caracter a dibujar ('A'-'Z' o digitos simples).
 * @param color  Indice de color de la paleta global.
 */
void dibujar_caracter(int x, int y, char c, int color);

#endif // NOMBRE_H_INCLUDED
