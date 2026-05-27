/**
 * @file pagina_menu.h
 * @brief Pagina del menu principal: JUGAR, AJUSTES, SALIR.
 *
 * Sigue la misma convencion que pagina_juego:
 *  - pagina_menu_inicializar() prepara el estado interno
 *  - pagina_menu_actualizar()  procesa el input y devuelve la opcion elegida
 *  - pagina_menu_dibujar()     renderiza el menu completo
 *
 * @version 1.0
 */

#ifndef PAGINA_MENU_H_INCLUDED
#define PAGINA_MENU_H_INCLUDED

#include "layout.h"
#include "fuente.h"
#include "primitivas.h"

/* ========================================================================== */
/* CONSTANTES                                                                 */
/* ========================================================================== */

#define MENU_CANT_OPCIONES      3
#define MENU_BOTON_JUGAR        1
#define MENU_BOTON_AJUSTES      2
#define MENU_BOTON_SALIR        3

#define MENU_COLOR_NORMAL       14  ///< Color del boton no seleccionado
#define MENU_COLOR_SELECCIONADO  6  ///< Color del boton seleccionado
#define MENU_COLOR_TEXTO        13  ///< Color del texto de los botones

#define MENU_BOTON_ANCHO_BASE   70  ///< Ancho base del boton en CGA
#define MENU_BOTON_ALTO_BASE     8  ///< Alto base del boton en CGA
#define MENU_SEPARACION_BASE    10  ///< Separacion base entre botones en CGA

/* ========================================================================== */
/* TDA                                                                        */
/* ========================================================================== */

typedef struct {
    int seleccion_actual;   ///< Boton actualmente resaltado (1 a MENU_CANT_OPCIONES)
    int opcion_elegida;     ///< Boton confirmado con ENTER (0 si no se eligio ninguno)
    int cantidad_opciones;
} t_menu;

/* ========================================================================== */
/* PROTOTIPOS                                                                 */
/* ========================================================================== */

/**
 * @brief Inicializa el estado del menu.
 *        La seleccion arranca en MENU_BOTON_JUGAR.
 */
void pagina_menu_inicializar(t_menu *menu);

/**
 * @brief Procesa el input del teclado y actualiza la seleccion.
 *
 * @return  La opcion elegida (MENU_BOTON_*) si se presiono ENTER, 0 si no.
 */
int pagina_menu_actualizar(t_menu *menu);

/**
 * @brief Dibuja el menu completo centrado en la posicion indicada.
 *
 * @param layout    Layout activo con escala y dimensiones.
 * @param menu      Estado actual del menu.
 * @param x         X del borde izquierdo del primer boton.
 * @param y         Y del borde superior del primer boton.
 */
void pagina_menu_dibujar(const t_layout *layout, const t_menu *menu, int x, int y);

#endif // PAGINA_MENU_H_INCLUDED
