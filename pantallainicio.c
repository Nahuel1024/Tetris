/**
 * @file pantallainicio.c
 * @brief HUD de la pantalla de juego: paneles laterales con puntaje,
 *        proximo tetromino y estadisticas por tipo de pieza.
 */

#include "pantallainicio.h"
#include "pantalla.h"
#include "fuente.h"
#include "paletacolor.h"

#define ANCHO_PANEL_IZQ     160
#define ALTO_PANEL_IZQ      220
#define ANCHO_PANEL_DER     160
#define ALTO_PANEL_DER      220
#define COLOR_FONDO_HUD     8
#define COLOR_BORDE         14
#define COLOR_TEXTO         15
#define COLOR_TITULO        13

static void dibujar_borde(int x, int y, int ancho, int alto, int color)
{
    for(int i = 0; i < ancho; i++)
        gbt_dibujar_pixel(x + i, y,            color); ///< Superior
    for(int i = 0; i < ancho; i++)
        gbt_dibujar_pixel(x + i, y + alto - 1, color); ///< Inferior
    for(int i = 0; i < alto; i++)
        gbt_dibujar_pixel(x,            y + i,  color); ///< Izquierdo
    for(int i = 0; i < alto; i++)
        gbt_dibujar_pixel(x + ancho - 1, y + i, color); ///< Derecho
}

static void dibujar_panel(int x, int y, int ancho, int alto)
{
    dibujar_rectangulo(x, y, ancho, alto, COLOR_FONDO_HUD);
    dibujar_borde(x, y, ancho, alto, COLOR_BORDE);
}

/**
 * @brief Calcula el offset X para centrar un texto dentro de un panel.
 *
 * Usa fuente_ancho_texto() para obtener el ancho real en pixels,
 * considerando la escala activa.
 *
 * @param ancho_panel  Ancho del panel en pixels.
 * @param texto        Cadena a centrar.
 * @param fuente       Fuente con la que se dibujara el texto.
 * @return             Offset X desde el borde izquierdo del panel.
 */
static int centrar_texto(int ancho_panel, const char *texto, const t_fuente *fuente)
{
    return (ancho_panel - fuente_ancho_texto(fuente, texto)) / 2;
}

void dibujar_hud(int margen_horizontal, int margen_vertical, int ancho_tablero)
{
    int x_panel_izq = margen_horizontal - ANCHO_PANEL_IZQ - 30;
    int y_panel_izq = margen_vertical;
    int x_panel_der = margen_horizontal + ancho_tablero + 30;
    int y_panel_der = margen_vertical;

    /// --- Panel izquierdo ---
    dibujar_panel(x_panel_izq, y_panel_izq, ANCHO_PANEL_IZQ, ALTO_PANEL_IZQ);

    fuente_dibujar_texto(&FUENTE_LARGE,
                         x_panel_izq + centrar_texto(ANCHO_PANEL_IZQ, "PUNTOS", &FUENTE_LARGE),
                         y_panel_izq + 15,
                         "PUNTOS", COLOR_TITULO);

    dibujar_rectangulo(x_panel_izq + 10, y_panel_izq + 30,
                       ANCHO_PANEL_IZQ - 20, 2, COLOR_BORDE);

    fuente_dibujar_texto(&FUENTE_LARGE,
                         x_panel_izq + centrar_texto(ANCHO_PANEL_IZQ, "0001250", &FUENTE_LARGE),
                         y_panel_izq + 60,
                         "0001250", COLOR_TEXTO);

    fuente_dibujar_texto(&FUENTE_LARGE,
                         x_panel_izq + centrar_texto(ANCHO_PANEL_IZQ, "PROXIMO TETRO", &FUENTE_LARGE),
                         y_panel_izq + 100,
                         "PROXIMO TETRO", COLOR_TITULO);

    dibujar_rectangulo(x_panel_izq + 10, y_panel_izq + 114,
                       ANCHO_PANEL_IZQ - 20, 2, COLOR_BORDE);

    /// Preview del proximo tetromino (pieza T hardcodeada por ahora)
    int base_x = x_panel_izq + 60;
    int base_y = y_panel_izq + 150;

    dibujar_cuadrado(base_x,                base_y,              2, TAM_CELDA);
    dibujar_cuadrado(base_x + TAM_CELDA,    base_y,              2, TAM_CELDA);
    dibujar_cuadrado(base_x + TAM_CELDA*2,  base_y,              2, TAM_CELDA);
    dibujar_cuadrado(base_x + TAM_CELDA,    base_y + TAM_CELDA,  2, TAM_CELDA);

    /// --- Panel derecho ---
    dibujar_panel(x_panel_der, y_panel_der, ANCHO_PANEL_DER, ALTO_PANEL_DER);

    fuente_dibujar_texto(&FUENTE_LARGE,
                         x_panel_der + centrar_texto(ANCHO_PANEL_DER, "TETROMINOS", &FUENTE_LARGE),
                         y_panel_der + 15,
                         "TETROMINOS", COLOR_TITULO);

    dibujar_rectangulo(x_panel_der + 10, y_panel_der + 30,
                       ANCHO_PANEL_DER - 20, 2, COLOR_BORDE);

    /// TODO: dibujar cada tetromino con su contador de apariciones
}
