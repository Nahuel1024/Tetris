/**
 * @file nombre.h
 * @brief Pantalla de ingreso de nombre de usuario mediante teclado en pantalla.
 * @version 1.2
 */

#ifndef NOMBRE_H_INCLUDED
#define NOMBRE_H_INCLUDED

#include "GBT/gbt.h"
#include <stdbool.h>
#include <string.h>

#include "layout.h"
#include "primitivas.h"
#include "fuente.h"
#include "paletacolor.h"

/* ========================================================================== */
/* CONSTANTES PROPIAS DEL MODULO                                              */
/* ========================================================================== */

#define NOMBRE_MAX_CHARS    3
#define TECLADO_FILAS       3
#define TECLADO_COLS        10
#define TAM_TECLA           18  ///< Tamanio base de tecla en CGA
#define SEP_TECLA           2   ///< Separacion base entre teclas en CGA

/* ========================================================================== */
/* ESTRUCTURA DE ESTADO                                                       */
/* ========================================================================== */

/**
 * @brief Estado completo de la pantalla de ingreso de nombre.
 *
 * El cursor puede estar en:
 *  - Fila 0 a TECLADO_FILAS-1: sobre el teclado QWERTY
 *  - Fila TECLADO_FILAS: sobre el boton ACEPTAR (fila virtual)
 */
typedef struct {
    char    buffer[NOMBRE_MAX_CHARS + 1];
    int     cursor_fila;
    int     cursor_col;
    int     cantidad_letras;
} t_estado_nombre;

/* ========================================================================== */
/* PROTOTIPOS PUBLICOS                                                        */
/* ========================================================================== */

void t_estado_nombre_inicializiar(t_estado_nombre *estado);
bool t_estado_nombre_completo(const t_estado_nombre *estado);

/**
 * @brief Muestra la pantalla de ingreso y bloquea hasta que el usuario
 *        complete el nombre y confirme con ACEPTAR.
 *
 * @param layout         Layout activo con escala y margenes.
 * @param nombre_destino Buffer destino (min NOMBRE_MAX_CHARS + 1 bytes).
 */
void pedir_nombre(const t_layout *layout, char *nombre_destino);

/**
 * @brief Dibuja el frame completo de la pantalla de ingreso.
 */
void dibujar_pantalla_nombre(const t_layout *layout, const t_estado_nombre *estado);

void dibujar_fondo_nombre(const t_layout *layout);
void dibujar_display_nombre(const t_layout *layout, const t_estado_nombre *estado);
void dibujar_letras_display(const t_layout *layout, const t_estado_nombre *estado);
void dibujar_teclado_nombre(const t_layout *layout, const t_estado_nombre *estado);
void dibujar_boton_aceptar(const t_layout *layout, bool activo);

#endif // NOMBRE_H_INCLUDED
