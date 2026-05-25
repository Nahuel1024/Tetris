/**
 * @file pantallainicio.c
 * @brief HUD de la pantalla de juego: paneles laterales con puntaje,
 *        proximo tetromino y estadisticas por tipo de pieza.
 */

#include "pantallainicio.h"

/* ========================================================================== */
/* CONSTANTES BASE (valores para CGA, escala 1.0)                            */
/* ========================================================================== */

#define PANEL_ANCHO_BASE        80  ///< Ancho base de cada panel lateral en CGA
#define PANEL_ALTO_BASE         110 ///< Alto base de cada panel lateral en CGA
#define PANEL_MARGEN_EXTERNO    15  ///< Separacion entre el tablero y el panel en CGA
#define PANEL_PADDING           5   ///< Margen interno del panel en CGA

#define LINEA_Y_TITULO          8   ///< Y relativa al panel donde va el titulo en CGA
#define LINEA_Y_SEPARADOR       18  ///< Y relativa al panel donde va la linea decorativa en CGA
#define LINEA_Y_VALOR           30  ///< Y relativa al panel donde va el valor (puntaje) en CGA
#define LINEA_Y_SUBTITULO       50  ///< Y relativa al panel donde va el subtitulo en CGA
#define LINEA_Y_SEPARADOR2      57  ///< Y relativa al panel donde va la segunda linea decorativa en CGA
#define LINEA_Y_PREVIEW         75  ///< Y relativa al panel donde va el preview del tetromino en CGA

#define COLOR_FONDO_HUD         INTERFAZ
#define COLOR_BORDE             14
#define COLOR_TEXTO             15
#define COLOR_TITULO            13

/* ========================================================================== */
/* HELPERS DE GEOMETRIA                                                       */
/* ========================================================================== */

static int panel_ancho(void)   { return (int)(PANEL_ANCHO_BASE    * escala_pantalla); }
static int panel_alto(void)    { return (int)(PANEL_ALTO_BASE     * escala_pantalla); }
static int margen_ext(void)    { return (int)(PANEL_MARGEN_EXTERNO * escala_pantalla); }
static int padding(void)       { return (int)(PANEL_PADDING        * escala_pantalla); }
static int linea_alto(void)    { return (int)(2                    * escala_pantalla); }

static int rel_y(int base)     { return (int)(base * escala_pantalla); }

/* ========================================================================== */
/* FUNCIONES ESTATICAS DE DIBUJO                                              */
/* ========================================================================== */

static void dibujar_borde(int x, int y, int ancho, int alto, int color)
{
    for(int i = 0; i < ancho; i++)
        gbt_dibujar_pixel(x + i, y,            color); ///< Superior
    for(int i = 0; i < ancho; i++)
        gbt_dibujar_pixel(x + i, y + alto - 1, color); ///< Inferior
    for(int i = 0; i < alto; i++)
        gbt_dibujar_pixel(x,             y + i, color); ///< Izquierdo
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
 * @param ancho_panel  Ancho del panel en pixels.
 * @param texto        Cadena a centrar.
 * @param fuente       Fuente con la que se dibujara el texto.
 * @return             Offset X desde el borde izquierdo del panel.
 */
static int centrar_texto(int ancho_panel, const char *texto, const t_fuente *fuente)
{
    return (ancho_panel - fuente_ancho_texto(fuente, texto)) / 2;
}

/* ========================================================================== */
/* DIBUJO DEL HUD                                                             */
/* ========================================================================== */

void dibujar_hud(int margen_horizontal, int margen_vertical, int ancho_tablero)
{
    int pw = panel_ancho();
    int ph = panel_alto();
    int me = margen_ext();
    int pd = padding();

    int x_izq = margen_horizontal - pw - me;
    int y_izq = margen_vertical;
    int x_der = margen_horizontal + ancho_tablero + me;
    int y_der = margen_vertical;

    /// --- Panel izquierdo: puntaje y preview ---
    dibujar_panel(x_izq, y_izq, pw, ph);

    fuente_dibujar_texto(&FUENTE_LARGE,
                         x_izq + centrar_texto(pw, "PUNTOS", &FUENTE_LARGE),
                         y_izq + rel_y(LINEA_Y_TITULO),
                         "PUNTOS", COLOR_TITULO);

    dibujar_rectangulo(x_izq + pd, y_izq + rel_y(LINEA_Y_SEPARADOR),
                       pw - pd * 2, linea_alto(), COLOR_BORDE);

    fuente_dibujar_texto(&FUENTE_LARGE,
                         x_izq + centrar_texto(pw, "0001250", &FUENTE_LARGE),
                         y_izq + rel_y(LINEA_Y_VALOR),
                         "0001250", COLOR_TEXTO);

    fuente_dibujar_texto(&FUENTE_LARGE,
                         x_izq + centrar_texto(pw, "PROXIMO", &FUENTE_LARGE),
                         y_izq + rel_y(LINEA_Y_SUBTITULO),
                         "PROXIMO", COLOR_TITULO);

    dibujar_rectangulo(x_izq + pd, y_izq + rel_y(LINEA_Y_SEPARADOR2),
                       pw - pd * 2, linea_alto(), COLOR_BORDE);

    /// Preview del proximo tetromino (pieza T hardcodeada por ahora)
    int base_x = x_izq + (pw - TAM_CELDA * 3) / 2;
    int base_y = y_izq + rel_y(LINEA_Y_PREVIEW);

    dibujar_cuadrado(base_x,                base_y,             T, TAM_CELDA);
    dibujar_cuadrado(base_x + TAM_CELDA,    base_y,             T, TAM_CELDA);
    dibujar_cuadrado(base_x + TAM_CELDA*2,  base_y,             T, TAM_CELDA);
    dibujar_cuadrado(base_x + TAM_CELDA,    base_y + TAM_CELDA, T, TAM_CELDA);

    /// --- Panel derecho: estadisticas por tetromino ---
    dibujar_panel(x_der, y_der, pw, ph);

    fuente_dibujar_texto(&FUENTE_LARGE,
                         x_der + centrar_texto(pw, "TETROS", &FUENTE_LARGE),
                         y_der + rel_y(LINEA_Y_TITULO),
                         "TETROS", COLOR_TITULO);

    dibujar_rectangulo(x_der + pd, y_der + rel_y(LINEA_Y_SEPARADOR),
                       pw - pd * 2, linea_alto(), COLOR_BORDE);

    /// TODO: dibujar cada tetromino con su contador de apariciones
}
