/**
 * @file pantalla_game_over.c
 * @brief Implementacion de la pantalla de fin de juego.
 */

#include "pantalla_game_over.h"
#include "GBT/gbt_entrada.h"
#include <stdio.h>

/* ========================================================================== */
/* HELPERS DE GEOMETRIA                                                       */
/* ========================================================================== */

static int boton_ancho(const t_layout *l)
{
    return (int)(GAME_OVER_BOTON_ANCHO_BASE * l->escala_pantalla);
}

static int boton_alto(const t_layout *l)
{
    return (int)(GAME_OVER_BOTON_ALTO_BASE * l->escala_pantalla);
}

static int boton_sep(const t_layout *l)
{
    return (int)(GAME_OVER_BOTON_SEP_BASE * l->escala_pantalla);
}

/* ========================================================================== */
/* HELPER DE DIBUJO DE BOTON                                                  */
/* ========================================================================== */

static void dibujar_boton(const t_layout *layout,
                           int x, int y, int ancho, int alto,
                           const char *texto, bool activo)
{
    int color_fondo = activo ? GAME_OVER_COLOR_BOTON_ACTIVO
                             : GAME_OVER_COLOR_BOTON_NORMAL;

    dibujar_rectangulo(layout, x, y, ancho, alto, color_fondo);

    int texto_ancho = fuente_ancho_texto(&FUENTE_MENU_8x8, layout, texto);
    int texto_alto  = fuente_alto_glifo(&FUENTE_MENU_8x8, layout);

    fuente_dibujar_texto(&FUENTE_MENU_8x8, layout,
                          x + (ancho - texto_ancho) / 2,
                          y + (alto  - texto_alto)  / 2,
                          texto, GAME_OVER_COLOR_BOTON_TEXTO);
}

/* ========================================================================== */
/* DIBUJO DE LA PANTALLA                                                      */
/* ========================================================================== */

void pantalla_game_over_dibujar(const t_layout *layout,
                                 const char *nombre, int puntaje, int cursor)
{
    int bw          = boton_ancho(layout);
    int bh          = boton_alto(layout);
    int bs          = boton_sep(layout);
    int alto_glifo  = fuente_alto_glifo(&FUENTE_MENU_8x8, layout);
    int sep_lineas  = (int)(8 * layout->escala_pantalla);

    /// Fondo
    dibujar_rectangulo(layout, 0, layout->margen_y,
                       layout->ancho_sistema, layout->alto_visible,
                       GAME_OVER_COLOR_FONDO);

    /// "GAME OVER" centrado al 20% del area visible
    int titulo_ancho = fuente_ancho_texto(&FUENTE_MENU_8x8, layout, "GAME OVER");
    int titulo_y     = layout->margen_y + (int)(layout->alto_visible * 0.20);
    fuente_dibujar_texto(&FUENTE_MENU_8x8, layout,
                          (layout->ancho_sistema - titulo_ancho) / 2,
                          titulo_y,
                          "GAME OVER", GAME_OVER_COLOR_TITULO);

    /// Nombre del jugador debajo del titulo
    int nombre_y     = titulo_y + alto_glifo + sep_lineas;
    int nombre_ancho = fuente_ancho_texto(&FUENTE_MENU_8x8, layout, nombre);
    fuente_dibujar_texto(&FUENTE_MENU_8x8, layout,
                          (layout->ancho_sistema - nombre_ancho) / 2,
                          nombre_y,
                          nombre, 14);

    /// Puntaje con 7 digitos y ceros a la izquierda, debajo del nombre
    char str_puntaje[8];
    sprintf(str_puntaje, "%07d", puntaje);
    int puntaje_y     = nombre_y + alto_glifo + sep_lineas;
    int puntaje_ancho = fuente_ancho_texto(&FUENTE_MENU_8x8, layout, str_puntaje);
    fuente_dibujar_texto(&FUENTE_MENU_8x8, layout,
                          (layout->ancho_sistema - puntaje_ancho) / 2,
                          puntaje_y,
                          str_puntaje, GAME_OVER_COLOR_PUNTAJE);

    /// Botones MENU y SALIR centrados al 65% del area visible
    int botones_total = bw * 2 + bs;
    int botones_x     = (layout->ancho_sistema - botones_total) / 2;
    int botones_y     = layout->margen_y + (int)(layout->alto_visible * 0.65);

    dibujar_boton(layout, botones_x,          botones_y, bw, bh,
                  "MENU",  cursor == GAME_OVER_OPC_MENU);
    dibujar_boton(layout, botones_x + bw + bs, botones_y, bw, bh,
                  "SALIR", cursor == GAME_OVER_OPC_SALIR);
}

/* ========================================================================== */
/* LOOP PRINCIPAL                                                              */
/* ========================================================================== */

int pantalla_game_over_ejecutar(const t_layout *layout,
                                 const char *nombre, int puntaje)
{
    int cursor = GAME_OVER_OPC_MENU;

    while(1)
    {
        gbt_borrar_backbuffer(0);
        pantalla_game_over_dibujar(layout, nombre, puntaje, cursor);
        gbt_volcar_backbuffer();

        gbt_procesar_entrada();

        if(gbt_tecla_presionada(GBTK_DERECHA) || gbt_tecla_presionada(GBTK_ABAJO))
        {
            cursor++;
            if(cursor > GAME_OVER_CANT_OPCIONES)
                cursor = 1;
        }

        if(gbt_tecla_presionada(GBTK_IZQUIERDA) || gbt_tecla_presionada(GBTK_ARRIBA))
        {
            cursor--;
            if(cursor < 1)
                cursor = GAME_OVER_CANT_OPCIONES;
        }

        if(gbt_tecla_presionada(GBTK_ENTER))
        {
            if(cursor == GAME_OVER_OPC_MENU)
                return GAME_OVER_MENU;
            if(cursor == GAME_OVER_OPC_SALIR)
                return GAME_OVER_SALIR;
        }
    }
}
