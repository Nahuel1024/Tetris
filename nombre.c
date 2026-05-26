/**
 * @file nombre.c
 * @brief Implementacion de la pantalla de ingreso de nombre con teclado en pantalla.
 *
 * Todas las funciones de dibujo reciben const t_layout* en lugar de
 * acceder a variables globales, siguiendo el mismo patron que pagina_juego.c.
 */

#include "nombre.h"

/* ========================================================================== */
/* LAYOUT DEL TECLADO QWERTY                                                  */
/* ========================================================================== */

#define TECLA_BORRAR        '\x01'
#define TECLA_BORRAR_CONT   '\x02'
#define COL_BORRAR          7

static const char TECLADO[TECLADO_FILAS][TECLADO_COLS] = {
    {'Q','W','E','R','T','Y','U','I','O','P'},
    {'A','S','D','F','G','H','J','K','L','\0'},
    {'Z','X','C','V','B','N','M',TECLA_BORRAR,TECLA_BORRAR_CONT,TECLA_BORRAR_CONT}
};

/* ========================================================================== */
/* COLORES                                                                    */
/* ========================================================================== */

#define COLOR_FONDO_PANTALLA    BORDE
#define COLOR_DISPLAY_BORDE     FONDO
#define COLOR_DISPLAY_FONDO     INTERFAZ
#define COLOR_TECLA_NORMAL      INTERFAZ
#define COLOR_TECLA_CURSOR      J
#define COLOR_TEXTO_TECLA       14
#define COLOR_TEXTO_DISPLAY     O
#define COLOR_BOTON_NORMAL      INTERFAZ
#define COLOR_BOTON_ACTIVO      J
#define COLOR_BOTON_TEXTO       BORDE
#define COLOR_TITULO            14

/* ========================================================================== */
/* CONSTANTES DE DISEÑO                                                       */
/* ========================================================================== */

#define DISPLAY_PADDING         4
#define DISPLAY_BORDE_EXT       2
#define DISPLAY_BORDE_INT       2
#define SLOT_ANCHO_BASE         22
#define SLOT_ALTO_BASE          22
#define CURSOR_MARGEN_INF       3
#define CURSOR_ALTO             2
#define BORRAR_TECLAS_ANCHO     3
#define ACEPTAR_ANCHO_BASE      60
#define ACEPTAR_ALTO_BASE       14
#define LAYOUT_Y_TITULO         0.03
#define LAYOUT_Y_DISPLAY        0.10
#define LAYOUT_Y_TECLADO        0.30
#define LAYOUT_Y_MARGEN_INF     0.04
#define FLECHA_CUERPO_LARGO     8
#define FLECHA_PUNTA_ALTO       5

/* ========================================================================== */
/* HELPERS DE GEOMETRIA (todos reciben layout)                                */
/* ========================================================================== */

static int ef(const t_layout *l)           { return (int)l->escala_pantalla; }
static int tam_tecla(const t_layout *l)    { return (int)(TAM_TECLA          * l->escala_pantalla); }
static int sep_tecla(const t_layout *l)    { return (int)(SEP_TECLA          * l->escala_pantalla); }
static int borde_ext(const t_layout *l)    { return (int)(DISPLAY_BORDE_EXT  * l->escala_pantalla); }
static int borde_int(const t_layout *l)    { return (int)(DISPLAY_BORDE_INT  * l->escala_pantalla); }
static int slot_ancho(const t_layout *l)   { return (int)(SLOT_ANCHO_BASE    * l->escala_pantalla); }
static int boton_ancho(const t_layout *l)  { return (int)(ACEPTAR_ANCHO_BASE * l->escala_pantalla); }
static int boton_alto(const t_layout *l)   { return (int)(ACEPTAR_ALTO_BASE  * l->escala_pantalla); }
static int gb(const t_layout *l)           { return (int)(DISPLAY_BORDE_EXT  * l->escala_pantalla); }

static int slot_alto_contenido(const t_layout *l)
{
    return (int)(SLOT_ALTO_BASE * l->escala_pantalla);
}

static int display_alto(const t_layout *l)
{
    return borde_ext(l) + slot_alto_contenido(l) + borde_ext(l);
}

static int display_ancho(const t_layout *l)
{
    return borde_ext(l)
           + NOMBRE_MAX_CHARS * slot_ancho(l)
           + (NOMBRE_MAX_CHARS - 1) * borde_int(l)
           + borde_ext(l);
}

static int ancho_teclado(const t_layout *l)
{
    return TECLADO_COLS * (tam_tecla(l) + sep_tecla(l)) - sep_tecla(l);
}

static int borrar_ancho(const t_layout *l)
{
    return BORRAR_TECLAS_ANCHO * tam_tecla(l) + (BORRAR_TECLAS_ANCHO - 1) * sep_tecla(l);
}

static int teclado_ini_x(const t_layout *l) { return (l->ancho_sistema - ancho_teclado(l)) / 2; }
static int display_ini_x(const t_layout *l) { return (l->ancho_sistema - display_ancho(l)) / 2; }
static int boton_ini_x(const t_layout *l)   { return (l->ancho_sistema - boton_ancho(l))   / 2; }

static int titulo_ini_y(const t_layout *l)
{
    return l->margen_y + (int)(l->alto_visible * LAYOUT_Y_TITULO);
}

static int display_ini_y(const t_layout *l)
{
    return l->margen_y + (int)(l->alto_visible * LAYOUT_Y_DISPLAY);
}

static int teclado_ini_y(const t_layout *l)
{
    return l->margen_y + (int)(l->alto_visible * LAYOUT_Y_TECLADO);
}

static int boton_ini_y(const t_layout *l)
{
    return l->margen_y + l->alto_visible
           - boton_alto(l)
           - (int)(l->alto_visible * LAYOUT_Y_MARGEN_INF);
}

/* ========================================================================== */
/* DIBUJO DE LA FLECHA DE BORRAR                                              */
/* ========================================================================== */

static void dibujar_flecha_borrar(const t_layout *l,
                                   int tx, int ty, int ancho, int alto, int color)
{
    int factor  = ef(l);
    int cx      = tx + ancho / 2;
    int cy      = ty + alto  / 2 - (int)(l->escala_pantalla + 0.5);
    int grosor  = factor;

    int cuerpo_largo = FLECHA_CUERPO_LARGO * factor;
    int cuerpo_ini_x = cx - cuerpo_largo / 2;

    for(int g = 0; g < grosor; g++)
        for(int i = 0; i < cuerpo_largo; i++)
            gbt_dibujar_pixel(cuerpo_ini_x + i, cy - grosor / 2 + g, color);

    int punta_alto = FLECHA_PUNTA_ALTO * factor;
    for(int fila = 0; fila < punta_alto; fila++)
    {
        int largo = fila + 1;
        int py    = cy - punta_alto / 2 + fila;
        if(fila >= punta_alto / 2)
            largo = punta_alto - fila;

        for(int i = 0; i < largo * factor; i++)
            gbt_dibujar_pixel(cuerpo_ini_x - largo * factor + i, py, color);
    }
}

/* ========================================================================== */
/* RENDERIZADO: COMPONENTES INDIVIDUALES                                      */
/* ========================================================================== */

void dibujar_fondo_nombre(const t_layout *layout)
{
    dibujar_rectangulo(layout, 0, layout->margen_y,
                       layout->ancho_sistema, layout->alto_visible,
                       COLOR_FONDO_PANTALLA);

    int titulo_x = (layout->ancho_sistema
                    - fuente_ancho_texto(&FUENTE_SMALL, layout, "INGRESE SU NOMBRE")) / 2;
    fuente_dibujar_texto(&FUENTE_SMALL, layout,
                         titulo_x, titulo_ini_y(layout),
                         "INGRESE SU NOMBRE", COLOR_TITULO);
}

void dibujar_display_nombre(const t_layout *layout, const t_estado_nombre *estado)
{
    (void)estado;

    int ini_x = display_ini_x(layout);
    int ini_y = display_ini_y(layout);
    int ancho = display_ancho(layout);
    int alto  = display_alto(layout);
    int be    = borde_ext(layout);
    int bi    = borde_int(layout);

    dibujar_rectangulo(layout, ini_x, ini_y, ancho, alto, COLOR_DISPLAY_BORDE);

    for(int i = 0; i < NOMBRE_MAX_CHARS; i++)
    {
        int slot_x = ini_x + be + i * (slot_ancho(layout) + bi);
        int slot_y = ini_y + be;
        dibujar_rectangulo(layout, slot_x, slot_y,
                           slot_ancho(layout), slot_alto_contenido(layout),
                           COLOR_DISPLAY_FONDO);
    }
}

void dibujar_letras_display(const t_layout *layout, const t_estado_nombre *estado)
{
    int ini_x          = display_ini_x(layout);
    int ini_y          = display_ini_y(layout);
    int be             = borde_ext(layout);
    int bi             = borde_int(layout);
    int alto_glifo     = fuente_alto_glifo(&FUENTE_SMALL, layout);
    int alto_contenido = slot_alto_contenido(layout);
    int ancho_glifo    = fuente_ancho_texto(&FUENTE_SMALL, layout, "A");

    for(int i = 0; i < estado->cantidad_letras; i++)
    {
        int slot_x  = ini_x + be + i * (slot_ancho(layout) + bi);
        int letra_x = slot_x + (slot_ancho(layout) - ancho_glifo) / 2;
        int letra_y = ini_y  + be + (alto_contenido - alto_glifo) / 2;
        fuente_dibujar_caracter(&FUENTE_SMALL, layout,
                                letra_x, letra_y,
                                estado->buffer[i], COLOR_TEXTO_DISPLAY);
    }

    if(estado->cantidad_letras < NOMBRE_MAX_CHARS)
    {
        int slot_x = ini_x + be + estado->cantidad_letras * (slot_ancho(layout) + bi);
        int cur_x  = slot_x + (int)(DISPLAY_PADDING * layout->escala_pantalla);
        int cur_y  = ini_y  + be + alto_contenido
                     - (int)(CURSOR_MARGEN_INF * layout->escala_pantalla);
        int cur_w  = slot_ancho(layout) - (int)(DISPLAY_PADDING * 2 * layout->escala_pantalla);
        int cur_h  = (int)(CURSOR_ALTO * layout->escala_pantalla);
        dibujar_rectangulo(layout, cur_x, cur_y, cur_w, cur_h, COLOR_TEXTO_DISPLAY);
    }
}

void dibujar_teclado_nombre(const t_layout *layout, const t_estado_nombre *estado)
{
    int ini_x       = teclado_ini_x(layout);
    int ini_y       = teclado_ini_y(layout);
    int tt          = tam_tecla(layout);
    int st          = sep_tecla(layout);
    int borde       = gb(layout);
    int ancho_glifo = fuente_ancho_texto(&FUENTE_SMALL, layout, "A");
    int alto_glifo  = fuente_alto_glifo(&FUENTE_SMALL, layout);

    for(int f = 0; f < TECLADO_FILAS; f++)
    {
        int sangria = (f == 1) ? (tt + st) / 2 : 0;

        for(int c = 0; c < TECLADO_COLS; c++)
        {
            char letra = TECLADO[f][c];

            if(letra == TECLA_BORRAR_CONT || letra == '\0')
                continue;

            int tx = ini_x + sangria + c * (tt + st);
            int ty = ini_y + f * (tt + st);

            bool es_cursor = (f == estado->cursor_fila && c == estado->cursor_col);

            if(letra == TECLA_BORRAR)
            {
                int bw          = borrar_ancho(layout);
                int color_fondo = es_cursor ? COLOR_BOTON_ACTIVO : COLOR_BOTON_NORMAL;

                dibujar_rectangulo(layout, tx, ty, bw, tt, color_fondo);
                dibujar_rectangulo(layout, tx,              ty + tt - borde, bw,    borde, COLOR_DISPLAY_BORDE);
                dibujar_rectangulo(layout, tx + bw - borde, ty,              borde, tt,    COLOR_DISPLAY_BORDE);
                dibujar_flecha_borrar(layout, tx, ty, bw, tt, COLOR_TEXTO_TECLA);
            }
            else
            {
                int color_fondo = es_cursor ? COLOR_TECLA_CURSOR : COLOR_TECLA_NORMAL;

                dibujar_rectangulo(layout, tx, ty, tt, tt, color_fondo);
                dibujar_rectangulo(layout, tx,             ty + tt - borde, tt,    borde, COLOR_DISPLAY_BORDE);
                dibujar_rectangulo(layout, tx + tt - borde, ty,             borde, tt,    COLOR_DISPLAY_BORDE);

                char str[2] = {letra, '\0'};
                fuente_dibujar_texto(&FUENTE_SMALL, layout,
                                     tx + (tt - ancho_glifo) / 2,
                                     ty + (tt - alto_glifo)  / 2,
                                     str, COLOR_TEXTO_TECLA);
            }
        }
    }
}

void dibujar_boton_aceptar(const t_layout *layout, bool activo)
{
    int ini_x  = boton_ini_x(layout);
    int ini_y  = boton_ini_y(layout);
    int ancho  = boton_ancho(layout);
    int alto   = boton_alto(layout);
    int borde  = gb(layout);

    dibujar_rectangulo(layout, ini_x, ini_y, ancho, alto,
                       activo ? COLOR_BOTON_ACTIVO : COLOR_BOTON_NORMAL);

    dibujar_rectangulo(layout, ini_x,               ini_y + alto - borde, ancho, borde, COLOR_DISPLAY_BORDE);
    dibujar_rectangulo(layout, ini_x + ancho - borde, ini_y,              borde, alto,  COLOR_DISPLAY_BORDE);

    int texto_ancho = fuente_ancho_texto(&FUENTE_SMALL, layout, "ACEPTAR");
    int texto_alto  = fuente_alto_glifo(&FUENTE_SMALL, layout);
    fuente_dibujar_texto(&FUENTE_SMALL, layout,
                         ini_x + (ancho - texto_ancho) / 2,
                         ini_y + (alto  - texto_alto)  / 2,
                         "ACEPTAR", COLOR_BOTON_TEXTO);
}

/* ========================================================================== */
/* ORQUESTADOR DE FRAME                                                       */
/* ========================================================================== */

void dibujar_pantalla_nombre(const t_layout *layout, const t_estado_nombre *estado)
{
    gbt_borrar_backbuffer(0);
    dibujar_fondo_nombre(layout);
    dibujar_display_nombre(layout, estado);
    dibujar_letras_display(layout, estado);
    dibujar_teclado_nombre(layout, estado);
    dibujar_boton_aceptar(layout, estado->cursor_fila == TECLADO_FILAS);
    gbt_volcar_backbuffer();
}

/* ========================================================================== */
/* HELPERS DE NAVEGACION                                                      */
/* ========================================================================== */

static bool celda_valida(int fila, int col)
{
    if(fila == TECLADO_FILAS)              return true;
    if(fila < 0 || fila >= TECLADO_FILAS)  return false;
    if(col  < 0 || col  >= TECLADO_COLS)   return false;
    char c = TECLADO[fila][col];
    return c != '\0' && c != TECLA_BORRAR_CONT;
}

static void mover_cursor(t_estado_nombre *estado, int dfila, int dcol)
{
    int nueva_fila = estado->cursor_fila + dfila;
    int nueva_col  = estado->cursor_col  + dcol;

    if(nueva_fila < 0 || nueva_fila > TECLADO_FILAS)
        return;

    if(nueva_fila == TECLADO_FILAS)
    {
        estado->cursor_fila = TECLADO_FILAS;
        return;
    }

    if(nueva_col < 0)              nueva_col = 0;
    if(nueva_col >= TECLADO_COLS)  nueva_col = TECLADO_COLS - 1;

    while(nueva_col >= 0 && !celda_valida(nueva_fila, nueva_col))
        nueva_col--;

    if(nueva_col >= 0 && celda_valida(nueva_fila, nueva_col))
    {
        estado->cursor_fila = nueva_fila;
        estado->cursor_col  = nueva_col;
    }
}

/* ========================================================================== */
/* PUNTO DE ENTRADA PRINCIPAL                                                 */
/* ========================================================================== */

void t_estado_nombre_inicializiar(t_estado_nombre *estado)
{
    strcpy(estado->buffer, "");
    estado->cursor_fila     = 0;
    estado->cursor_col      = 0;
    estado->cantidad_letras = 0;
}

bool t_estado_nombre_completo(const t_estado_nombre *estado)
{
    return estado->cantidad_letras == NOMBRE_MAX_CHARS;
}

void pedir_nombre(const t_layout *layout, char *nombre_destino)
{
    t_estado_nombre estado;
    t_estado_nombre_inicializiar(&estado);

    bool nombre_completo = false;

    while(!nombre_completo)
    {
        dibujar_pantalla_nombre(layout, &estado);
        gbt_procesar_entrada();

        if(gbt_tecla_presionada(GBTK_ARRIBA))
            mover_cursor(&estado, -1, 0);
        else if(gbt_tecla_presionada(GBTK_ABAJO))
            mover_cursor(&estado, +1, 0);
        else if(gbt_tecla_presionada(GBTK_IZQUIERDA))
            mover_cursor(&estado, 0, -1);
        else if(gbt_tecla_presionada(GBTK_DERECHA))
            mover_cursor(&estado, 0, +1);
        else if(gbt_tecla_presionada(GBTK_ENTER))
        {
            if(estado.cursor_fila == TECLADO_FILAS)
            {
                if(t_estado_nombre_completo(&estado))
                    nombre_completo = true;
            }
            else
            {
                char letra = TECLADO[estado.cursor_fila][estado.cursor_col];

                if(letra == TECLA_BORRAR)
                {
                    if(estado.cantidad_letras > 0)
                    {
                        estado.cantidad_letras--;
                        estado.buffer[estado.cantidad_letras] = '\0';
                        if(estado.cursor_fila == TECLADO_FILAS)
                            estado.cursor_fila = TECLADO_FILAS - 1;
                    }
                }
                else if(letra != '\0' && estado.cantidad_letras < NOMBRE_MAX_CHARS)
                {
                    estado.buffer[estado.cantidad_letras] = letra;
                    estado.cantidad_letras++;
                    if(t_estado_nombre_completo(&estado))
                        estado.cursor_fila = TECLADO_FILAS;
                }
            }
        }
    }

    estado.buffer[NOMBRE_MAX_CHARS] = '\0';
    strcpy(nombre_destino, estado.buffer);
}
