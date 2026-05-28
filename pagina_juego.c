/**
 * @file pagina_juego.c
 * @brief Implementacion del renderizado de la pantalla principal de juego.
 */

#include "pagina_juego.h"
#include "paletacolor.h"
#include "juego.h"
#include <stdio.h>

/* ========================================================================== */
/* CONSTANTES DEL HUD (valores base CGA)                                     */
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

#define PUNTAJE_DIGITOS         7   ///< Digitos del puntaje con ceros a la izquierda

#define COLOR_FONDO_HUD         INTERFAZ
#define COLOR_BORDE_HUD         14
#define COLOR_TEXTO_HUD         13
#define COLOR_TITULO_HUD        13

/* ========================================================================== */
/* HELPERS DE GEOMETRIA DEL HUD                                               */
/* ========================================================================== */

static int panel_ancho(const t_layout *l) { return (int)(PANEL_ANCHO_BASE     * l->escala_pantalla); }
static int panel_alto(const t_layout *l)  { return (int)(PANEL_ALTO_BASE      * l->escala_pantalla); }
static int margen_ext(const t_layout *l)  { return (int)(PANEL_MARGEN_EXTERNO * l->escala_pantalla); }
static int padding(const t_layout *l)     { return (int)(PANEL_PADDING        * l->escala_pantalla); }
static int linea_alto(const t_layout *l)  { return (int)(2                    * l->escala_pantalla); }
static int rel_y(const t_layout *l, int base) { return (int)(base * l->escala_pantalla); }

/* ========================================================================== */
/* FUNCIONES ESTATICAS DEL HUD                                                */
/* ========================================================================== */

static void dibujar_borde_panel(const t_layout *l, int x, int y, int ancho, int alto, int color)
{
    for(int i = 0; i < ancho; i++) gbt_dibujar_pixel(x + i, y,            color);
    for(int i = 0; i < ancho; i++) gbt_dibujar_pixel(x + i, y + alto - 1, color);
    for(int i = 0; i < alto;  i++) gbt_dibujar_pixel(x,             y + i, color);
    for(int i = 0; i < alto;  i++) gbt_dibujar_pixel(x + ancho - 1, y + i, color);
    (void)l;
}

static void dibujar_panel(const t_layout *l, int x, int y, int ancho, int alto)
{
    dibujar_rectangulo(l, x, y, ancho, alto, COLOR_FONDO_HUD);
    dibujar_borde_panel(l, x, y, ancho, alto, COLOR_BORDE_HUD);
}

static int centrar_en_panel(const t_layout *l, int ancho_panel, const char *texto)
{
    return (ancho_panel - fuente_ancho_texto(&FUENTE_LARGE, l, texto)) / 2;
}

static void dibujar_preview(const t_layout *l, int x_panel, int y_panel,
                             const t_tetromino *siguiente)
{
    int pw    = panel_ancho(l);
    int tc    = l->tam_celda;
    int color = (int)siguiente->mino[0].color;

    int minos_ancho;
    switch(siguiente->pieza)
    {
        case 'I': minos_ancho = 4; break;
        case 'O': minos_ancho = 2; break;
        default:  minos_ancho = 3; break;
    }

    int base_x = x_panel + (pw - minos_ancho * tc) / 2;
    int base_y = y_panel + rel_y(l, LINEA_Y_PREVIEW);

    switch(siguiente->pieza)
    {
        case 'I':
            dibujar_cuadrado_3d(l, base_x,        base_y, color, tc);
            dibujar_cuadrado_3d(l, base_x + tc,   base_y, color, tc);
            dibujar_cuadrado_3d(l, base_x + tc*2, base_y, color, tc);
            dibujar_cuadrado_3d(l, base_x + tc*3, base_y, color, tc);
            break;
        case 'O':
            dibujar_cuadrado_3d(l, base_x,      base_y,      color, tc);
            dibujar_cuadrado_3d(l, base_x + tc, base_y,      color, tc);
            dibujar_cuadrado_3d(l, base_x,      base_y + tc, color, tc);
            dibujar_cuadrado_3d(l, base_x + tc, base_y + tc, color, tc);
            break;
        case 'T':
            dibujar_cuadrado_3d(l, base_x + tc,   base_y,      color, tc);
            dibujar_cuadrado_3d(l, base_x,         base_y + tc, color, tc);
            dibujar_cuadrado_3d(l, base_x + tc,   base_y + tc, color, tc);
            dibujar_cuadrado_3d(l, base_x + tc*2, base_y + tc, color, tc);
            break;
        case 'S':
            dibujar_cuadrado_3d(l, base_x + tc,   base_y,      color, tc);
            dibujar_cuadrado_3d(l, base_x + tc*2, base_y,      color, tc);
            dibujar_cuadrado_3d(l, base_x,        base_y + tc, color, tc);
            dibujar_cuadrado_3d(l, base_x + tc,   base_y + tc, color, tc);
            break;
        case 'Z':
            dibujar_cuadrado_3d(l, base_x,        base_y,      color, tc);
            dibujar_cuadrado_3d(l, base_x + tc,   base_y,      color, tc);
            dibujar_cuadrado_3d(l, base_x + tc,   base_y + tc, color, tc);
            dibujar_cuadrado_3d(l, base_x + tc*2, base_y + tc, color, tc);
            break;
        case 'L':
            dibujar_cuadrado_3d(l, base_x + tc*2, base_y,      color, tc);
            dibujar_cuadrado_3d(l, base_x,        base_y + tc, color, tc);
            dibujar_cuadrado_3d(l, base_x + tc,   base_y + tc, color, tc);
            dibujar_cuadrado_3d(l, base_x + tc*2, base_y + tc, color, tc);
            break;
        case 'J':
            dibujar_cuadrado_3d(l, base_x,        base_y,      color, tc);
            dibujar_cuadrado_3d(l, base_x,        base_y + tc, color, tc);
            dibujar_cuadrado_3d(l, base_x + tc,   base_y + tc, color, tc);
            dibujar_cuadrado_3d(l, base_x + tc*2, base_y + tc, color, tc);
            break;
    }
}

/* ========================================================================== */
/* COMPONENTES PUBLICOS                                                       */
/* ========================================================================== */

void dibujar_fondo_juego(const t_layout *layout)
{
    dibujar_rectangulo(layout, 0, layout->margen_y,
                       layout->ancho_sistema, layout->alto_visible, FONDO);
}

void dibujar_tablero(const t_layout *layout, const t_tablero *tablero)
{
    for(int i = 2; i < (int)tablero->dimensiones.alto; i++)
    {
        for(int j = 0; j < (int)tablero->dimensiones.ancho; j++)
        {
            int x = layout->margen_horizontal + j * layout->tam_celda;
            int y = layout->margen_vertical   + (i - FILAS_SPAWN) * layout->tam_celda;
            dibujar_cuadrado_3d(layout, x, y,
                                tablero->celda[i][j].color,
                                layout->tam_celda);
        }
    }
}

void dibujar_pieza(const t_layout *layout, const t_tetromino *tetromino)
{
    for(int i = 0; i < CANTIDAD_MINOS; i++)
    {
        if(!mino_en_area_spawn(&tetromino->mino[i]))
        {
            int x = layout->margen_horizontal
                    + tetromino->mino[i].coordenadas.columna * layout->tam_celda;
            int y = layout->margen_vertical
                    + (tetromino->mino[i].coordenadas.fila - FILAS_SPAWN) * layout->tam_celda;
            dibujar_cuadrado_3d(layout, x, y,
                                (int)tetromino->mino[i].color,
                                layout->tam_celda);
        }
    }
}

void dibujar_hud(const t_layout *layout, const t_tetromino *siguiente, int puntaje)
{
    int pw = panel_ancho(layout);
    int ph = panel_alto(layout);
    int me = margen_ext(layout);
    int pd = padding(layout);

    int x_izq = layout->margen_horizontal - pw - me;
    int y_izq = layout->margen_vertical;
    int x_der = layout->margen_horizontal + layout->ancho_tablero + me;
    int y_der = layout->margen_vertical;

    /// --- Panel izquierdo: puntaje y preview ---
    dibujar_panel(layout, x_izq, y_izq, pw, ph);

    fuente_dibujar_texto(&FUENTE_LARGE, layout,
                         x_izq + centrar_en_panel(layout, pw, "PUNTOS"),
                         y_izq + rel_y(layout, LINEA_Y_TITULO),
                         "PUNTOS", COLOR_TITULO_HUD);

    dibujar_rectangulo(layout, x_izq + pd, y_izq + rel_y(layout, LINEA_Y_SEPARADOR),
                       pw - pd * 2, linea_alto(layout), COLOR_BORDE_HUD);

    /// Puntaje con ceros a la izquierda
    char str_puntaje[PUNTAJE_DIGITOS + 1];
    sprintf(str_puntaje, "%0*d", PUNTAJE_DIGITOS, puntaje);
    fuente_dibujar_texto(&FUENTE_LARGE, layout,
                         x_izq + centrar_en_panel(layout, pw, str_puntaje),
                         y_izq + rel_y(layout, LINEA_Y_VALOR),
                         str_puntaje, COLOR_TEXTO_HUD);

    fuente_dibujar_texto(&FUENTE_LARGE, layout,
                         x_izq + centrar_en_panel(layout, pw, "PROXIMO"),
                         y_izq + rel_y(layout, LINEA_Y_SUBTITULO),
                         "PROXIMO", COLOR_TITULO_HUD);

    dibujar_rectangulo(layout, x_izq + pd, y_izq + rel_y(layout, LINEA_Y_SEPARADOR2),
                       pw - pd * 2, linea_alto(layout), COLOR_BORDE_HUD);

    dibujar_preview(layout, x_izq, y_izq, siguiente);

    /// --- Panel derecho: estadisticas por tetromino ---
    dibujar_panel(layout, x_der, y_der, pw, ph);

    fuente_dibujar_texto(&FUENTE_LARGE, layout,
                         x_der + centrar_en_panel(layout, pw, "TETROS"),
                         y_der + rel_y(layout, LINEA_Y_TITULO),
                         "TETROS", COLOR_TITULO_HUD);

    dibujar_rectangulo(layout, x_der + pd, y_der + rel_y(layout, LINEA_Y_SEPARADOR),
                       pw - pd * 2, linea_alto(layout), COLOR_BORDE_HUD);

    /// TODO: dibujar cada tetromino con su contador de apariciones
}

void dibujar_cartel_pausa(const t_layout *layout)
{
    int cartel_ancho = (int)(280 * layout->escala_pantalla);
    int cartel_alto  = (int)(120 * layout->escala_pantalla);
    int cartel_x     = (layout->ancho_sistema - cartel_ancho) / 2;
    int cartel_y     = layout->margen_y + (layout->alto_visible - cartel_alto) / 2;
    int borde        = (int)(4 * layout->escala_pantalla);

    dibujar_rectangulo(layout, cartel_x, cartel_y, cartel_ancho, cartel_alto, FONDO);

    dibujar_rectangulo(layout, cartel_x,                        cartel_y,                       cartel_ancho, borde,       BORDE);
    dibujar_rectangulo(layout, cartel_x,                        cartel_y + cartel_alto - borde, cartel_ancho, borde,       BORDE);
    dibujar_rectangulo(layout, cartel_x,                        cartel_y,                       borde,        cartel_alto, BORDE);
    dibujar_rectangulo(layout, cartel_x + cartel_ancho - borde, cartel_y,                       borde,        cartel_alto, BORDE);

    fuente_dibujar_texto(&FUENTE_LARGE, layout,
                         cartel_x + (cartel_ancho - fuente_ancho_texto(&FUENTE_LARGE, layout, "PAUSA")) / 2,
                         cartel_y + (int)(40 * layout->escala_pantalla),
                         "PAUSA", BORDE);

    fuente_dibujar_texto(&FUENTE_LARGE, layout,
                         cartel_x + (cartel_ancho - fuente_ancho_texto(&FUENTE_LARGE, layout, "ENTER PARA CONTINUAR")) / 2,
                         cartel_y + (int)(80 * layout->escala_pantalla),
                         "ENTER PARA CONTINUAR", BORDE);
}

/* ========================================================================== */
/* ORQUESTADOR                                                                */
/* ========================================================================== */

void dibujar_juego(const t_layout *layout, const t_tablero *tablero,
                   const t_tetromino *tetromino, const t_tetromino *siguiente,
                   int puntaje)
{
    gbt_borrar_backbuffer(0);
    dibujar_fondo_juego(layout);
    dibujar_hud(layout, siguiente, puntaje);
    dibujar_tablero(layout, tablero);
    dibujar_pieza(layout, tetromino);
    gbt_volcar_backbuffer();
}
