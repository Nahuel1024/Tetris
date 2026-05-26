/**
 * @file pantallainicio.c
 * @brief HUD de la pantalla de juego: paneles laterales con puntaje,
 *        proximo tetromino y estadisticas por tipo de pieza.
 */

#include "pantallainicio.h"
#include "pantalla.h"
#include "fuente.h"
#include "paletacolor.h"

/* ========================================================================== */
/* CONSTANTES BASE (valores para CGA, escala 1.0)                            */
/* ========================================================================== */

#define PANEL_ANCHO_BASE        80
#define PANEL_ALTO_BASE         110
#define PANEL_MARGEN_EXTERNO    15
#define PANEL_PADDING           5

#define LINEA_Y_TITULO          8
#define LINEA_Y_SEPARADOR       18
#define LINEA_Y_VALOR           30
#define LINEA_Y_SUBTITULO       50
#define LINEA_Y_SEPARADOR2      57
#define LINEA_Y_PREVIEW         75

#define COLOR_FONDO_HUD         INTERFAZ
#define COLOR_BORDE             14
#define COLOR_TEXTO             15
#define COLOR_TITULO            13

/* ========================================================================== */
/* HELPERS DE GEOMETRIA                                                       */
/* ========================================================================== */

static int panel_ancho(void) { return (int)(PANEL_ANCHO_BASE     * escala_pantalla); }
static int panel_alto(void)  { return (int)(PANEL_ALTO_BASE      * escala_pantalla); }
static int margen_ext(void)  { return (int)(PANEL_MARGEN_EXTERNO * escala_pantalla); }
static int padding(void)     { return (int)(PANEL_PADDING        * escala_pantalla); }
static int linea_alto(void)  { return (int)(2                    * escala_pantalla); }
static int rel_y(int base)   { return (int)(base * escala_pantalla); }

/* ========================================================================== */
/* FUNCIONES ESTATICAS DE DIBUJO                                              */
/* ========================================================================== */

static void dibujar_borde(int x, int y, int ancho, int alto, int color)
{
    for(int i = 0; i < ancho; i++)
        gbt_dibujar_pixel(x + i, y,            color);
    for(int i = 0; i < ancho; i++)
        gbt_dibujar_pixel(x + i, y + alto - 1, color);
    for(int i = 0; i < alto; i++)
        gbt_dibujar_pixel(x,             y + i, color);
    for(int i = 0; i < alto; i++)
        gbt_dibujar_pixel(x + ancho - 1, y + i, color);
}

static void dibujar_panel(int x, int y, int ancho, int alto)
{
    dibujar_rectangulo(x, y, ancho, alto, COLOR_FONDO_HUD);
    dibujar_borde(x, y, ancho, alto, COLOR_BORDE);
}

static int centrar_texto(int ancho_panel, const char *texto, const t_fuente *fuente)
{
    return (ancho_panel - fuente_ancho_texto(fuente, texto)) / 2;
}

/**
 * @brief Dibuja el preview del tetromino siguiente centrado dentro del panel.
 *
 * Calcula la forma del tetromino a partir de su campo 'pieza' para determinar
 * el ancho en minos y centrarlo horizontalmente. Cada mino se dibuja con
 * su color correspondiente usando dibujar_cuadrado().
 *
 * @param x_panel   X inicial del panel izquierdo.
 * @param y_panel   Y inicial del panel izquierdo.
 * @param siguiente Tetromino siguiente a previsualizar.
 */
static void dibujar_preview(int x_panel, int y_panel, const t_tetromino *siguiente)
{
    /// Determinamos el ancho en minos segun el tipo de pieza
    /// I ocupa 4 columnas, O ocupa 2, el resto ocupa 3
    int minos_ancho;
    switch(siguiente->pieza)
    {
        case 'I': minos_ancho = 4; break;
        case 'O': minos_ancho = 2; break;
        default:  minos_ancho = 3; break;
    }

    int pw      = panel_ancho();
    int base_x  = x_panel + (pw - minos_ancho * TAM_CELDA) / 2;
    int base_y  = y_panel + rel_y(LINEA_Y_PREVIEW);
    int color   = siguiente->mino[0].color;

    switch(siguiente->pieza)
    {
        case 'I':
            dibujar_cuadrado(base_x,                base_y, color, TAM_CELDA);
            dibujar_cuadrado(base_x + TAM_CELDA,    base_y, color, TAM_CELDA);
            dibujar_cuadrado(base_x + TAM_CELDA*2,  base_y, color, TAM_CELDA);
            dibujar_cuadrado(base_x + TAM_CELDA*3,  base_y, color, TAM_CELDA);
            break;
        case 'O':
            dibujar_cuadrado(base_x,             base_y,             color, TAM_CELDA);
            dibujar_cuadrado(base_x + TAM_CELDA, base_y,             color, TAM_CELDA);
            dibujar_cuadrado(base_x,             base_y + TAM_CELDA, color, TAM_CELDA);
            dibujar_cuadrado(base_x + TAM_CELDA, base_y + TAM_CELDA, color, TAM_CELDA);
            break;
        case 'T':
            dibujar_cuadrado(base_x + TAM_CELDA, base_y,             color, TAM_CELDA);
            dibujar_cuadrado(base_x,             base_y + TAM_CELDA, color, TAM_CELDA);
            dibujar_cuadrado(base_x + TAM_CELDA, base_y + TAM_CELDA, color, TAM_CELDA);
            dibujar_cuadrado(base_x + TAM_CELDA*2, base_y + TAM_CELDA, color, TAM_CELDA);
            break;
        case 'S':
            dibujar_cuadrado(base_x + TAM_CELDA,   base_y,             color, TAM_CELDA);
            dibujar_cuadrado(base_x + TAM_CELDA*2,  base_y,            color, TAM_CELDA);
            dibujar_cuadrado(base_x,                base_y + TAM_CELDA, color, TAM_CELDA);
            dibujar_cuadrado(base_x + TAM_CELDA,    base_y + TAM_CELDA, color, TAM_CELDA);
            break;
        case 'Z':
            dibujar_cuadrado(base_x,                base_y,             color, TAM_CELDA);
            dibujar_cuadrado(base_x + TAM_CELDA,    base_y,             color, TAM_CELDA);
            dibujar_cuadrado(base_x + TAM_CELDA,    base_y + TAM_CELDA, color, TAM_CELDA);
            dibujar_cuadrado(base_x + TAM_CELDA*2,  base_y + TAM_CELDA, color, TAM_CELDA);
            break;
        case 'L':
            dibujar_cuadrado(base_x + TAM_CELDA*2,  base_y,             color, TAM_CELDA);
            dibujar_cuadrado(base_x,                base_y + TAM_CELDA, color, TAM_CELDA);
            dibujar_cuadrado(base_x + TAM_CELDA,    base_y + TAM_CELDA, color, TAM_CELDA);
            dibujar_cuadrado(base_x + TAM_CELDA*2,  base_y + TAM_CELDA, color, TAM_CELDA);
            break;
        case 'J':
            dibujar_cuadrado(base_x,                base_y,             color, TAM_CELDA);
            dibujar_cuadrado(base_x,                base_y + TAM_CELDA, color, TAM_CELDA);
            dibujar_cuadrado(base_x + TAM_CELDA,    base_y + TAM_CELDA, color, TAM_CELDA);
            dibujar_cuadrado(base_x + TAM_CELDA*2,  base_y + TAM_CELDA, color, TAM_CELDA);
            break;
    }
}

/* ========================================================================== */
/* DIBUJO DEL HUD                                                             */
/* ========================================================================== */

void dibujar_hud(int margen_horizontal, int margen_vertical,
                 int ancho_tablero, const t_tetromino *siguiente)
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

    dibujar_preview(x_izq, y_izq, siguiente);

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
