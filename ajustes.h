/**
 * @file ajustes.h
 * @brief TDA y pagina de ajustes del juego.
 *
 * Permite al usuario modificar:
 *  - Resolucion: CGA (0) o VGA (1)
 *  - Velocidad de caida: 0.1 a 1.0 segundos en escalas de 0.1
 *
 * Los cambios no se aplican hasta que el usuario confirma con el
 * boton APLICAR. El boton VOLVER descarta los cambios y regresa
 * al menu principal.
 *
 * Uso tipico (desde main):
 *   t_ajustes ajustes;
 *   ajustes_inicializar(&ajustes, resolucion_actual, velocidad_actual);
 *
 *   int resultado = pagina_ajustes_ejecutar(&layout, &ajustes, &tablero);
 *   if(resultado == AJUSTES_APLICAR)
 *   {
 *       resolucion = ajustes.resolucion;
 *       velocidad  = ajustes.velocidad;
 *       // layout ya fue recalculado dentro de pagina_ajustes_ejecutar
 *   }
 *
 * @version 1.0
 */

#ifndef AJUSTES_H_INCLUDED
#define AJUSTES_H_INCLUDED

#include "layout.h"
#include "fuente.h"
#include "primitivas.h"
#include "paletacolor.h"
#include "GBT/gbt.h"

/* ========================================================================== */
/* CONSTANTES                                                                 */
/* ========================================================================== */

#define AJUSTES_RES_CGA         0
#define AJUSTES_RES_VGA         1

#define AJUSTES_VEL_MIN         0.1
#define AJUSTES_VEL_MAX         1.0
#define AJUSTES_VEL_PASO        0.1

/// Valores de retorno de pagina_ajustes_ejecutar()
#define AJUSTES_APLICAR         1   ///< Usuario confirmo los cambios
#define AJUSTES_VOLVER          2   ///< Usuario volvio sin cambios

/// Cantidad de opciones navegables (2 ajustes + 2 botones)
#define AJUSTES_CANT_OPCIONES   4
#define AJUSTES_OPC_RESOLUCION  1
#define AJUSTES_OPC_VELOCIDAD   2
#define AJUSTES_OPC_APLICAR     3
#define AJUSTES_OPC_VOLVER      4

/// Dimensiones base de los controles (CGA)
#define AJUSTES_FILA_ALTO_BASE      14  ///< Alto de cada fila de ajuste
#define AJUSTES_FILA_SEP_BASE        6  ///< Separacion entre filas
#define AJUSTES_BOTON_ANCHO_BASE    50  ///< Ancho de los botones APLICAR/VOLVER
#define AJUSTES_BOTON_ALTO_BASE     10  ///< Alto de los botones
#define AJUSTES_BOTON_SEP_BASE      10  ///< Separacion entre botones

/// Colores
#define AJUSTES_COLOR_FONDO         BORDE
#define AJUSTES_COLOR_FILA_NORMAL   INTERFAZ
#define AJUSTES_COLOR_FILA_ACTIVA   J
#define AJUSTES_COLOR_TEXTO         14
#define AJUSTES_COLOR_VALOR         O
#define AJUSTES_COLOR_BOTON_NORMAL  INTERFAZ
#define AJUSTES_COLOR_BOTON_ACTIVO  J
#define AJUSTES_COLOR_BOTON_TEXTO   14

/* ========================================================================== */
/* TDA                                                                        */
/* ========================================================================== */

/**
 * @brief Estado de los ajustes del juego.
 *
 * Contiene los valores actuales (que pueden estar editandose)
 * y los valores originales para poder descartar cambios al volver.
 */
typedef struct {
    int    resolucion;          ///< Resolucion activa: AJUSTES_RES_CGA o AJUSTES_RES_VGA
    double velocidad;           ///< Velocidad de caida en segundos (0.1 a 1.0)
    int    resolucion_original; ///< Valor al entrar a ajustes (para descartar)
    int velocidad_original;  ///< Valor al entrar a ajustes (para descartar)
    int    cursor;              ///< Opcion actualmente seleccionada (1 a AJUSTES_CANT_OPCIONES)
} t_ajustes;

/* ========================================================================== */
/* PROTOTIPOS                                                                 */
/* ========================================================================== */

/**
 * @brief Inicializa el estado de ajustes con los valores actuales del juego.
 *
 * @param ajustes     Puntero al estado a inicializar.
 * @param resolucion  Resolucion activa al momento de abrir ajustes.
 * @param velocidad   Velocidad de caida activa al momento de abrir ajustes.
 */
void ajustes_inicializar(t_ajustes *ajustes, int resolucion, double velocidad);

/**
 * @brief Ejecuta el loop completo de la pantalla de ajustes.
 *
 * Dibuja la pantalla, procesa el input y bloquea hasta que el usuario
 * presiona APLICAR o VOLVER.
 * Si el usuario cambia la resolucion y aplica, destruye la ventana actual
 * y crea una nueva, recalculando el layout.
 *
 * @param layout   Layout activo. Se actualiza in-place si cambia la resolucion.
 * @param ajustes  Estado de ajustes con los valores a editar.
 * @param tablero  Tablero activo, necesario para recalcular el layout.
 * @return         AJUSTES_APLICAR si se confirmaron cambios, AJUSTES_VOLVER si no.
 */
int pagina_ajustes_ejecutar(t_layout *layout, t_ajustes *ajustes,
                             const t_tablero *tablero);

/**
 * @brief Dibuja el frame completo de la pantalla de ajustes.
 *
 * @param layout   Layout activo.
 * @param ajustes  Estado actual de los ajustes.
 */
void pagina_ajustes_dibujar(const t_layout *layout, const t_ajustes *ajustes);

#endif // AJUSTES_H_INCLUDED
