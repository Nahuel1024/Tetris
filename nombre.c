/**
 * @file nombre.c
 * @brief Implementacion de la pantalla de ingreso de nombre con teclado en pantalla.
 */

#include "nombre.h"

/* ========================================================================== */
/* FUENTE BITMAP 5x7                                                          */
/* ========================================================================== */

static const uint8_t FUENTE_5x7[26][7] = {
    /* A */ {0x0E,0x11,0x11,0x1F,0x11,0x11,0x11},
    /* B */ {0x1E,0x11,0x11,0x1E,0x11,0x11,0x1E},
    /* C */ {0x0E,0x11,0x10,0x10,0x10,0x11,0x0E},
    /* D */ {0x1E,0x11,0x11,0x11,0x11,0x11,0x1E},
    /* E */ {0x1F,0x10,0x10,0x1E,0x10,0x10,0x1F},
    /* F */ {0x1F,0x10,0x10,0x1E,0x10,0x10,0x10},
    /* G */ {0x0E,0x11,0x10,0x17,0x11,0x11,0x0F},
    /* H */ {0x11,0x11,0x11,0x1F,0x11,0x11,0x11},
    /* I */ {0x0E,0x04,0x04,0x04,0x04,0x04,0x0E},
    /* J */ {0x07,0x02,0x02,0x02,0x02,0x12,0x0C},
    /* K */ {0x11,0x12,0x14,0x18,0x14,0x12,0x11},
    /* L */ {0x10,0x10,0x10,0x10,0x10,0x10,0x1F},
    /* M */ {0x11,0x1B,0x15,0x15,0x11,0x11,0x11},
    /* N */ {0x11,0x19,0x15,0x13,0x11,0x11,0x11},
    /* O */ {0x0E,0x11,0x11,0x11,0x11,0x11,0x0E},
    /* P */ {0x1E,0x11,0x11,0x1E,0x10,0x10,0x10},
    /* Q */ {0x0E,0x11,0x11,0x11,0x15,0x12,0x0D},
    /* R */ {0x1E,0x11,0x11,0x1E,0x14,0x12,0x11},
    /* S */ {0x0F,0x10,0x10,0x0E,0x01,0x01,0x1E},
    /* T */ {0x1F,0x04,0x04,0x04,0x04,0x04,0x04},
    /* U */ {0x11,0x11,0x11,0x11,0x11,0x11,0x0E},
    /* V */ {0x11,0x11,0x11,0x11,0x11,0x0A,0x04},
    /* W */ {0x11,0x11,0x11,0x15,0x15,0x1B,0x11},
    /* X */ {0x11,0x11,0x0A,0x04,0x0A,0x11,0x11},
    /* Y */ {0x11,0x11,0x0A,0x04,0x04,0x04,0x04},
    /* Z */ {0x1F,0x01,0x02,0x04,0x08,0x10,0x1F},
};

/* ========================================================================== */
/* LAYOUT DEL TECLADO QWERTY                                                  */
/* ========================================================================== */

#define TECLA_BORRAR        '\x01'  ///< Marca el inicio del boton BORRAR en el array
#define TECLA_BORRAR_CONT   '\x02'  ///< Continuacion del boton BORRAR (se saltea al dibujar)
#define COL_BORRAR          7       ///< Columna donde empieza el boton BORRAR en la fila 2

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
/* FUENTE BITMAP: DIMENSIONES Y ESPACIADO                                     */
/* ========================================================================== */

#define FUENTE_FILAS            7   ///< Alto de cada glifo en pixeles logicos
#define FUENTE_COLS             5   ///< Ancho de cada glifo en pixeles logicos
#define FUENTE_MASCARA_INICIO   0x10 ///< Bit mas significativo de los 5 usados por fila
#define FUENTE_ESPACIADO        6   ///< Pixeles base entre el inicio de dos caracteres consecutivos

/* ========================================================================== */
/* DISPLAY DE NOMBRE                                                          */
/* ========================================================================== */

#define DISPLAY_PADDING         4   ///< Margen interior a cada lado del contenido del slot
#define DISPLAY_BORDE_EXT       2   ///< Grosor del marco perimetral del display
#define DISPLAY_BORDE_INT       2   ///< Grosor de los separadores verticales entre slots
#define SLOT_ANCHO_BASE         22  ///< Ancho base de cada slot en CGA
#define SLOT_ALTO_BASE          22  ///< Alto base del contenido de cada slot en CGA
#define CURSOR_MARGEN_INF       3   ///< Distancia en px desde el fondo del slot al subrayado
#define CURSOR_ALTO             2   ///< Alto del subrayado indicador de posicion activa

/* ========================================================================== */
/* TECLADO EN PANTALLA                                                        */
/* ========================================================================== */

#define BORRAR_TECLAS_ANCHO     3   ///< Cantidad de teclas que ocupa el boton BORRAR

/* ========================================================================== */
/* BOTON ACEPTAR                                                              */
/* ========================================================================== */

#define ACEPTAR_ANCHO_BASE      60  ///< Ancho base del boton ACEPTAR en CGA
#define ACEPTAR_ALTO_BASE       14  ///< Alto base del boton ACEPTAR en CGA

/* ========================================================================== */
/* PROPORCIONES DE LAYOUT VERTICAL (fraccion de alto_visible)                */
/* ========================================================================== */

#define LAYOUT_Y_TITULO         0.03 ///< Titulo: 3% desde el tope del area visible
#define LAYOUT_Y_DISPLAY        0.10 ///< Display: 10% desde el tope del area visible
#define LAYOUT_Y_TECLADO        0.30 ///< Teclado: 30% desde el tope del area visible
#define LAYOUT_Y_MARGEN_INF     0.04 ///< Boton ACEPTAR: 4% de margen desde el fondo

/* ========================================================================== */
/* FLECHA DEL BOTON BORRAR                                                    */
/* ========================================================================== */

#define FLECHA_CUERPO_LARGO     8   ///< Largo base del cuerpo horizontal de la flecha
#define FLECHA_PUNTA_ALTO       5   ///< Alto base del triangulo de la punta
#define FLECHA_COLA_LARGO       4   ///< Largo base de cada diagonal de la muesca

/* ========================================================================== */
/* HELPERS DE GEOMETRIA                                                       */
/* ========================================================================== */

static int ef(void)         { return (int)escala_pantalla; }
static int tam_tecla(void)  { return (int)(TAM_TECLA        * escala_pantalla); }
static int sep_tecla(void)  { return (int)(SEP_TECLA        * escala_pantalla); }
static int borde_ext(void)  { return (int)(DISPLAY_BORDE_EXT * escala_pantalla); }
static int borde_int(void)  { return (int)(DISPLAY_BORDE_INT * escala_pantalla); }
static int slot_ancho(void) { return (int)(SLOT_ANCHO_BASE   * escala_pantalla); }
static int boton_ancho(void){ return (int)(ACEPTAR_ANCHO_BASE * escala_pantalla); }
static int boton_alto(void) { return (int)(ACEPTAR_ALTO_BASE  * escala_pantalla); }
static int gb(void)         { return (int)(DISPLAY_BORDE_EXT  * escala_pantalla); }

static int slot_alto_contenido(void) { return (int)(SLOT_ALTO_BASE * escala_pantalla); }

static int display_alto(void)
{
    return borde_ext() + slot_alto_contenido() + borde_ext();
}

static int display_ancho(void)
{
    return borde_ext()
           + NOMBRE_MAX_CHARS * slot_ancho()
           + (NOMBRE_MAX_CHARS - 1) * borde_int()
           + borde_ext();
}

static int ancho_teclado(void)
{
    return TECLADO_COLS * (tam_tecla() + sep_tecla()) - sep_tecla();
}

/**
 * Ancho del boton BORRAR: BORRAR_TECLAS_ANCHO teclas + separadores entre ellas.
 * Garantiza simetria visual con la fila Q-P del teclado.
 */
static int borrar_ancho(void)
{
    return BORRAR_TECLAS_ANCHO * tam_tecla() + (BORRAR_TECLAS_ANCHO - 1) * sep_tecla();
}

static int teclado_ini_x(void)  { return (ancho_sistema - ancho_teclado()) / 2; }
static int display_ini_x(void)  { return (ancho_sistema - display_ancho()) / 2; }
static int boton_ini_x(void)    { return (ancho_sistema - boton_ancho())   / 2; }

static int titulo_ini_y(void)
{
    return margen_y + (int)(alto_visible * LAYOUT_Y_TITULO);
}

static int display_ini_y(void)
{
    return margen_y + (int)(alto_visible * LAYOUT_Y_DISPLAY);
}

static int teclado_ini_y(void)
{
    return margen_y + (int)(alto_visible * LAYOUT_Y_TECLADO);
}

static int boton_ini_y(void)
{
    return margen_y + alto_visible - boton_alto() - (int)(alto_visible * LAYOUT_Y_MARGEN_INF);
}

/* ========================================================================== */
/* PRIMITIVA DE TEXTO BITMAP                                                  */
/* ========================================================================== */

void dibujar_caracter(int x, int y, char c, int color)
{
    if(c < 'A' || c > 'Z')
        return;

    int idx    = c - 'A';
    int factor = ef();

    for(int fila = 0; fila < FUENTE_FILAS; fila++)
    {
        uint8_t mascara = FUENTE_5x7[idx][fila];
        for(int col = 0; col < FUENTE_COLS; col++)
        {
            if(mascara & (FUENTE_MASCARA_INICIO >> col))
            {
                for(int py = 0; py < factor; py++)
                    for(int px = 0; px < factor; px++)
                        gbt_dibujar_pixel(x + col * factor + px,
                                          y + fila * factor + py,
                                          color);
            }
        }
    }
}

static void dibujar_string(int x, int y, const char *str, int color)
{
    int factor = ef();
    while(*str)
    {
        dibujar_caracter(x, y, *str, color);
        x += FUENTE_ESPACIADO * factor;
        str++;
    }
}

/* ========================================================================== */
/* DIBUJO DE LA FLECHA DE BORRAR                                              */
/* ========================================================================== */

/**
 * @brief Dibuja una flecha hacia la izquierda centrada dentro del boton borrar.
 *
 * La flecha se construye con tres partes:
 *   - Cuerpo horizontal central
 *   - Punta triangular hacia la izquierda
 *   - Muesca en V en el extremo derecho (forma tipica de tecla backspace)
 *
 * @param tx     X inicial del boton borrar.
 * @param ty     Y inicial del boton borrar.
 * @param ancho  Ancho total del boton.
 * @param alto   Alto total del boton.
 * @param color  Color de la flecha.
 */
static void dibujar_flecha_borrar(int tx, int ty, int ancho, int alto, int color)
{
    int factor  = ef();
    int cx      = tx + ancho / 2;
    int cy      = ty + alto  / 2 - (int)(escala_pantalla + 0.5); // La última resta busca centralizar la flecha con respecto al efecto 3d
    int grosor  = factor;

    /// --- Cuerpo horizontal ---
    int cuerpo_largo = FLECHA_CUERPO_LARGO * factor;
    int cuerpo_ini_x = cx - cuerpo_largo / 2;
    for(int g = 0; g < grosor; g++)
        for(int i = 0; i < cuerpo_largo; i++)
            gbt_dibujar_pixel(cuerpo_ini_x + i, cy - grosor / 2 + g, color);

    /// --- Punta triangular hacia la izquierda ---
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

void dibujar_fondo_nombre(void)
{
    dibujar_rectangulo(0, margen_y, ancho_sistema, alto_visible, COLOR_FONDO_PANTALLA);

    int factor       = ef();
    int titulo_ancho = (int)strlen("INGRESE SU NOMBRE") * FUENTE_ESPACIADO * factor;
    int titulo_x     = (ancho_sistema - titulo_ancho) / 2;

    dibujar_string(titulo_x, titulo_ini_y(), "INGRESE SU NOMBRE", COLOR_TITULO);
}

void dibujar_display_nombre(const t_estado_nombre *estado)
{
    (void)estado;

    int ini_x = display_ini_x();
    int ini_y = display_ini_y();
    int ancho = display_ancho();
    int alto  = display_alto();
    int be    = borde_ext();
    int bi    = borde_int();

    /// 1. Marco perimetral completo
    dibujar_rectangulo(ini_x, ini_y, ancho, alto, COLOR_DISPLAY_BORDE);

    /// 2. Relleno de cada slot; los bordes quedan visibles automaticamente
    for(int i = 0; i < NOMBRE_MAX_CHARS; i++)
    {
        int slot_x = ini_x + be + i * (slot_ancho() + bi);
        int slot_y = ini_y + be;
        dibujar_rectangulo(slot_x, slot_y,
                           slot_ancho(), slot_alto_contenido(),
                           COLOR_DISPLAY_FONDO);
    }
}

void dibujar_letras_display(const t_estado_nombre *estado)
{
    int ini_x          = display_ini_x();
    int ini_y          = display_ini_y();
    int be             = borde_ext();
    int bi             = borde_int();
    int factor         = ef();
    int alto_glifo     = FUENTE_FILAS * factor;
    int alto_contenido = slot_alto_contenido();

    for(int i = 0; i < estado->cantidad_letras; i++)
    {
        int slot_x  = ini_x + be + i * (slot_ancho() + bi);
        int letra_x = slot_x + (slot_ancho() - FUENTE_COLS * factor) / 2;
        int letra_y = ini_y  + be + (alto_contenido - alto_glifo) / 2;
        dibujar_caracter(letra_x, letra_y, estado->buffer[i], COLOR_TEXTO_DISPLAY);
    }

    /// Subrayado en el slot activo si el nombre no esta completo
    if(estado->cantidad_letras < NOMBRE_MAX_CHARS)
    {
        int slot_x = ini_x + be + estado->cantidad_letras * (slot_ancho() + bi);
        int cur_x  = slot_x + (int)(DISPLAY_PADDING * escala_pantalla);
        int cur_y  = ini_y  + be + alto_contenido - (int)(CURSOR_MARGEN_INF * escala_pantalla);
        int cur_w  = slot_ancho() - (int)(DISPLAY_PADDING * 2 * escala_pantalla);
        int cur_h  = (int)(CURSOR_ALTO * escala_pantalla);
        dibujar_rectangulo(cur_x, cur_y, cur_w, cur_h, COLOR_TEXTO_DISPLAY);
    }
}

void dibujar_teclado(const t_estado_nombre *estado)
{
    int ini_x  = teclado_ini_x();
    int ini_y  = teclado_ini_y();
    int tt     = tam_tecla();
    int st     = sep_tecla();
    int factor = ef();
    int borde  = gb();

    for(int f = 0; f < TECLADO_FILAS; f++)
    {
        /// La fila del medio (A-L) tiene sangria de media tecla
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
                int bw          = borrar_ancho();
                int color_fondo = es_cursor ? COLOR_BOTON_ACTIVO : COLOR_BOTON_NORMAL;

                dibujar_rectangulo(tx, ty, bw, tt, color_fondo);
                dibujar_rectangulo(tx,            ty + tt - borde, bw,    borde, COLOR_DISPLAY_BORDE);
                dibujar_rectangulo(tx + bw - borde, ty,            borde, tt,    COLOR_DISPLAY_BORDE);

                dibujar_flecha_borrar(tx, ty, bw, tt, COLOR_TEXTO_TECLA);
            }
            else
            {
                int color_fondo = es_cursor ? COLOR_TECLA_CURSOR : COLOR_TECLA_NORMAL;

                dibujar_rectangulo(tx, ty, tt, tt, color_fondo);
                dibujar_rectangulo(tx,           ty + tt - borde, tt,    borde, COLOR_DISPLAY_BORDE);
                dibujar_rectangulo(tx + tt - borde, ty,           borde, tt,    COLOR_DISPLAY_BORDE);

                dibujar_caracter(tx + (tt - FUENTE_COLS * factor) / 2,
                                 ty + (tt - FUENTE_FILAS * factor) / 2,
                                 letra, COLOR_TEXTO_TECLA);
            }
        }
    }
}

void dibujar_boton_aceptar(bool activo)
{
    int ini_x  = boton_ini_x();
    int ini_y  = boton_ini_y();
    int ancho  = boton_ancho();
    int alto   = boton_alto();
    int borde  = gb();
    int factor = ef();

    dibujar_rectangulo(ini_x, ini_y, ancho, alto,
                       activo ? COLOR_BOTON_ACTIVO : COLOR_BOTON_NORMAL);

    dibujar_rectangulo(ini_x,             ini_y + alto - borde, ancho, borde, COLOR_DISPLAY_BORDE);
    dibujar_rectangulo(ini_x + ancho - borde, ini_y,            borde, alto,  COLOR_DISPLAY_BORDE);

    int texto_ancho = (int)strlen("ACEPTAR") * FUENTE_ESPACIADO * factor;
    int texto_alto  = FUENTE_FILAS * factor;
    dibujar_string(ini_x + (ancho - texto_ancho) / 2,
                   ini_y + (alto  - texto_alto)  / 2,
                   "ACEPTAR", COLOR_BOTON_TEXTO);
}

/* ========================================================================== */
/* ORQUESTADOR DE FRAME                                                       */
/* ========================================================================== */

void dibujar_pantalla_nombre(const t_estado_nombre *estado)
{
    gbt_borrar_backbuffer(0);

    dibujar_fondo_nombre();
    dibujar_display_nombre(estado);
    dibujar_letras_display(estado);
    dibujar_teclado(estado);
    dibujar_boton_aceptar(estado->cursor_fila == TECLADO_FILAS);

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

void pedir_nombre(char *nombre_destino)
{
    t_estado_nombre estado;
    t_estado_nombre_inicializiar(&estado);

    bool nombre_completo = false;

    while(!nombre_completo)
    {
        dibujar_pantalla_nombre(&estado);
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
