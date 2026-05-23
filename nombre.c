/**
 * @file nombre.c
 * @brief Implementacion de la pantalla de ingreso de nombre con teclado en pantalla.
 *
 * Diseno general:
 *  - Layout QWERTY en 3 filas de 10 teclas (Q-P / A-L / Z-M + 2 vacias).
 *  - Debajo del teclado, un boton "ACEPTAR" que solo es funcional cuando
 *    el jugador ingreso exactamente NOMBRE_MAX_CHARS letras.
 *  - El cursor se mueve con las teclas de flecha; Enter selecciona.
 *  - Backspace (tecla especial mapeada al borde izquierdo) borra la ultima letra.
 *  - Cada glifo se dibuja con una fuente bitmap 5x7 propia (sin texto de GBT).
 *
 * Coordenadas de referencia (resolucion CGA 320x200):
 *  - Display de nombre:  centrado horizontalmente, y=20
 *  - Teclado:            centrado, y=60
 *  - Boton ACEPTAR:      centrado, y=170
 */

#include "nombre.h"

/* ========================================================================== */
/* FUENTE BITMAP 5x7                                                          */
/* ========================================================================== */

/**
 * Cada entrada es un arreglo de 7 bytes; cada byte representa una fila de 5 bits
 * (bit 4 = pixel izquierdo, bit 0 = pixel derecho).
 * Solo se definen A-Z (indices 0-25).
 */
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

/** Tres filas del teclado; cada fila tiene exactamente TECLADO_COLS caracteres. */
static const char TECLADO[TECLADO_FILAS][TECLADO_COLS] = {
    {'Q','W','E','R','T','Y','U','I','O','P'},
    {'A','S','D','F','G','H','J','K','L','\0'}, ///< '\0' = posicion vacia
    {'Z','X','C','V','B','N','M','\0','\0','\0'}
};

/* ========================================================================== */
/* COLORES (indices de la paleta global definida en paletacolor.h)            */
/* ========================================================================== */

#define COLOR_FONDO_PANTALLA    BORDE       ///< 7: Fondo oscuro     (0x0A, 0x0A, 0x14)
#define COLOR_DISPLAY_BORDE     FONDO       ///< 9: Gris neutro      (0xC8, 0xC8, 0xC8)
#define COLOR_DISPLAY_FONDO     INTERFAZ    ///< 8: Azul muy oscuro  (0x28, 0x28, 0x3C)
#define COLOR_TECLA_NORMAL      INTERFAZ    ///< 8: Azul muy oscuro  (0x28, 0x28, 0x3C)
#define COLOR_TECLA_CURSOR      J           ///< 5: Azul vivo        (0x00, 0x64, 0xFF) - tecla activa
#define COLOR_TEXTO_TECLA       15          ///< 15: Blanco          (0xFF, 0xFF, 0xFF)
#define COLOR_TEXTO_DISPLAY     O           ///< 1: Amarillo         (0xFF, 0xDC, 0x00) - letras ingresadas
#define COLOR_BOTON_NORMAL      S           ///< 3: Verde claro      (0x00, 0xFF, 0x64)
#define COLOR_BOTON_ACTIVO      I           ///< 0: Celeste          (0x00, 0xC8, 0xFF) - boton resaltado
#define COLOR_BOTON_TEXTO       BORDE       ///< 7: Oscuro sobre claro (legibilidad)
#define COLOR_TITULO            15          ///< 15: Blanco          (0xFF, 0xFF, 0xFF)

/* ========================================================================== */
/* HELPERS DE GEOMETRIA                                                       */
/* ========================================================================== */

/** Ancho total del bloque de teclado en pixeles. */
#define ANCHO_TECLADO   (TECLADO_COLS * (TAM_TECLA + SEP_TECLA) - SEP_TECLA)

/** Calcula la X del teclado para que quede centrado horizontalmente. */
static int teclado_ini_x(void)
{
    return (ANCHO_CGA - ANCHO_TECLADO) / 2;
}

/** Y donde empieza el teclado. */
#define TECLADO_INI_Y   60

/** Dimensiones del display de nombre (3 celdas + separadores). */
#define DISPLAY_ANCHO   ((NOMBRE_MAX_CHARS) * 22 + 8)
#define DISPLAY_ALTO    26
#define DISPLAY_INI_Y   20
#define DISPLAY_INI_X   ((ANCHO_CGA - DISPLAY_ANCHO) / 2)

/** Boton ACEPTAR. */
#define BOTON_ANCHO     60
#define BOTON_ALTO      14
#define BOTON_INI_X     ((ANCHO_CGA - BOTON_ANCHO) / 2)
#define BOTON_INI_Y     178

/* ========================================================================== */
/* PRIMITIVA DE TEXTO BITMAP                                                  */
/* ========================================================================== */

void dibujar_caracter(int x, int y, char c, int color)
{
    if(c < 'A' || c > 'Z')
        return;

    int idx = c - 'A';

    for(int fila = 0; fila < 7; fila++)
    {
        uint8_t mascara = FUENTE_5x7[idx][fila];
        for(int col = 0; col < 5; col++)
        {
            if(mascara & (0x10 >> col))
                gbt_dibujar_pixel(x + col, y + fila, color);
        }
    }
}

/**
 * @brief Dibuja una cadena de caracteres espaciados 7px entre si.
 */
static void dibujar_string(int x, int y, const char *str, int color)
{
    while(*str)
    {
        dibujar_caracter(x, y, *str, color);
        x += 7;
        str++;
    }
}

/* ========================================================================== */
/* RENDERIZADO: COMPONENTES INDIVIDUALES                                      */
/* ========================================================================== */

void dibujar_fondo_nombre(void)
{
    dibujar_rectangulo(0, 0, ANCHO_CGA, ALTO_CGA, COLOR_FONDO_PANTALLA);

    /// Titulo "INGRESE SU NOMBRE" centrado arriba
    /// Texto: 17 caracteres * 7px = 119px
    int titulo_x = (ANCHO_CGA - 17 * 6) / 2;
    dibujar_string(titulo_x, 6, "INGRESE NOMBRE", COLOR_TITULO);
}

void dibujar_display_nombre(const t_estado_nombre *estado)
{
    (void)estado; ///< Reservado para posibles variaciones visuales futuras

    /// Marco exterior del display
    dibujar_rectangulo(DISPLAY_INI_X - 2,
                       DISPLAY_INI_Y - 2,
                       DISPLAY_ANCHO + 4,
                       DISPLAY_ALTO + 4,
                       COLOR_DISPLAY_BORDE);

    /// Relleno interior
    dibujar_rectangulo(DISPLAY_INI_X,
                       DISPLAY_INI_Y,
                       DISPLAY_ANCHO,
                       DISPLAY_ALTO,
                       COLOR_DISPLAY_FONDO);

    /// Separadores entre los 3 slots de letras
    for(int i = 1; i < NOMBRE_MAX_CHARS; i++)
    {
        int sep_x = DISPLAY_INI_X + i * 22 + 4;
        dibujar_rectangulo(sep_x, DISPLAY_INI_Y, 2, DISPLAY_ALTO, COLOR_DISPLAY_BORDE);
    }
}

void dibujar_letras_display(const t_estado_nombre *estado)
{
    for(int i = 0; i < estado->cantidad_letras; i++)
    {
        /// Cada slot ocupa 22px; centramos el glifo 5x7 dentro
        int letra_x = DISPLAY_INI_X + i * 22 + 8;
        int letra_y = DISPLAY_INI_Y + (DISPLAY_ALTO - 7) / 2;
        dibujar_caracter(letra_x, letra_y, estado->buffer[i], COLOR_TEXTO_DISPLAY);
    }

    /// Cursor parpadeante: subrayado en el slot activo
    if(estado->cantidad_letras < NOMBRE_MAX_CHARS)
    {
        int cur_x = DISPLAY_INI_X + estado->cantidad_letras * 22 + 5;
        int cur_y = DISPLAY_INI_Y + DISPLAY_ALTO - 4;
        dibujar_rectangulo(cur_x, cur_y, 12, 2, COLOR_TEXTO_DISPLAY);
    }
}

void dibujar_teclado(const t_estado_nombre *estado)
{
    int ini_x = teclado_ini_x();

    for(int f = 0; f < TECLADO_FILAS; f++)
    {
        /// La fila 1 (A-L) tiene sangria de media tecla para simular QWERTY
        int sangria = (f == 1) ? (TAM_TECLA + SEP_TECLA) / 2 : 0;

        for(int c = 0; c < TECLADO_COLS; c++)
        {
            char letra = TECLADO[f][c];

            int tx = ini_x + sangria + c * (TAM_TECLA + SEP_TECLA);
            int ty = TECLADO_INI_Y + f * (TAM_TECLA + SEP_TECLA);

            if(letra == '\0')
                continue; ///< Celda vacia, no se dibuja

            bool es_cursor = (f == estado->cursor_fila && c == estado->cursor_col);
            int color_fondo = es_cursor ? COLOR_TECLA_CURSOR : COLOR_TECLA_NORMAL;

            /// Cuerpo de la tecla
            dibujar_rectangulo(tx, ty, TAM_TECLA, TAM_TECLA, color_fondo);

            /// Borde inferior/derecho oscuro (efecto 3D simple)
            dibujar_rectangulo(tx,              ty + TAM_TECLA - 1, TAM_TECLA, 1, COLOR_DISPLAY_BORDE);
            dibujar_rectangulo(tx + TAM_TECLA - 1, ty,             1, TAM_TECLA, COLOR_DISPLAY_BORDE);

            /// Glifo centrado dentro de la tecla: (18 - 5) / 2 = 6px margen
            dibujar_caracter(tx + 6,
                             ty + (TAM_TECLA - 7) / 2,
                             letra,
                             COLOR_TEXTO_TECLA);
        }
    }
}

void dibujar_boton_aceptar(bool activo)
{
    int color_fondo = activo ? COLOR_BOTON_ACTIVO : COLOR_BOTON_NORMAL;

    dibujar_rectangulo(BOTON_INI_X, BOTON_INI_Y, BOTON_ANCHO, BOTON_ALTO, color_fondo);

    /// Borde
    dibujar_rectangulo(BOTON_INI_X,              BOTON_INI_Y + BOTON_ALTO - 1, BOTON_ANCHO, 1, COLOR_DISPLAY_BORDE);
    dibujar_rectangulo(BOTON_INI_X + BOTON_ANCHO - 1, BOTON_INI_Y,            1, BOTON_ALTO, COLOR_DISPLAY_BORDE);

    /// Texto "ACEPTAR" (7 chars * 7px = 49px; centrado en 60px -> margen ~5px)
    dibujar_string(BOTON_INI_X + 6,
                   BOTON_INI_Y + (BOTON_ALTO - 7) / 2,
                   "ACEPTAR",
                   COLOR_BOTON_TEXTO);
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

    /// El boton se resalta si el cursor esta en la fila "virtual" 3
    bool boton_activo = (estado->cursor_fila == TECLADO_FILAS);
    dibujar_boton_aceptar(boton_activo);

    gbt_volcar_backbuffer();
}

/* ========================================================================== */
/* HELPERS DE NAVEGACION                                                      */
/* ========================================================================== */

/**
 * @brief Devuelve true si la celda (fila, col) tiene una letra valida.
 */
static bool celda_valida(int fila, int col)
{
    if(fila == TECLADO_FILAS)   ///< Fila virtual del boton ACEPTAR
        return true;
    if(fila < 0 || fila >= TECLADO_FILAS)
        return false;
    if(col < 0 || col >= TECLADO_COLS)
        return false;
    return TECLADO[fila][col] != '\0';
}

/**
 * @brief Mueve el cursor en la direccion indicada, saltando celdas vacias.
 *
 * @param estado  Estado a modificar.
 * @param dfila   Desplazamiento de fila (-1, 0 o +1).
 * @param dcol    Desplazamiento de columna (-1, 0 o +1).
 */
static void mover_cursor(t_estado_nombre *estado, int dfila, int dcol)
{
    int nueva_fila = estado->cursor_fila + dfila;
    int nueva_col  = estado->cursor_col  + dcol;

    /// Limites verticales: 0 hasta TECLADO_FILAS (la fila extra es el boton)
    if(nueva_fila < 0 || nueva_fila > TECLADO_FILAS)
        return;

    /// Al entrar al boton, no importa la columna
    if(nueva_fila == TECLADO_FILAS)
    {
        estado->cursor_fila = TECLADO_FILAS;
        return;
    }

    /// Ajustar columna a rango valido
    if(nueva_col < 0)
        nueva_col = 0;
    if(nueva_col >= TECLADO_COLS)
        nueva_col = TECLADO_COLS - 1;

    /// Si la celda destino esta vacia, buscar la mas cercana a la izquierda
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

void pedir_nombre(char *nombre_destino)
{
    t_estado_nombre estado;
    memset(&estado, 0, sizeof(t_estado_nombre));
    estado.cursor_fila = 0;
    estado.cursor_col  = 0;

    bool nombre_completo = false;

    while(!nombre_completo)
    {
        dibujar_pantalla_nombre(&estado);

        /**
         * Procesamos la cola de eventos del sistema para actualizar
         * el estado de todas las teclas en este ciclo.
         * Luego consultamos cada tecla de interes individualmente con
         * gbt_tecla_presionada(), que maneja correctamente tanto los
         * valores ASCII como los codigos extendidos de las flechas
         * (generados con GBT_CODIGO_A_TECLA).
         */
        gbt_procesar_entrada();

        /// --- Navegacion ---
        if(gbt_tecla_presionada(GBTK_ARRIBA))
            mover_cursor(&estado, -1, 0);

        else if(gbt_tecla_presionada(GBTK_ABAJO))
            mover_cursor(&estado, +1, 0);

        else if(gbt_tecla_presionada(GBTK_IZQUIERDA))
            mover_cursor(&estado, 0, -1);

        else if(gbt_tecla_presionada(GBTK_DERECHA))
            mover_cursor(&estado, 0, +1);

        /// --- Confirmar seleccion ---
        else if(gbt_tecla_presionada(GBTK_ENTER))
        {
            if(estado.cursor_fila == TECLADO_FILAS)
            {
                /// Boton ACEPTAR: solo confirma si el nombre esta completo
                if(estado.cantidad_letras == NOMBRE_MAX_CHARS)
                    nombre_completo = true;
            }
            else
            {
                char letra = TECLADO[estado.cursor_fila][estado.cursor_col];
                if(letra != '\0' && estado.cantidad_letras < NOMBRE_MAX_CHARS)
                {
                    estado.buffer[estado.cantidad_letras] = letra;
                    estado.cantidad_letras++;
                    /// Si se completo el nombre, mover cursor al boton automaticamente
                    if(estado.cantidad_letras == NOMBRE_MAX_CHARS)
                        estado.cursor_fila = TECLADO_FILAS;
                }
            }
        }

        /// --- Borrar ultima letra ---
        else if(gbt_tecla_presionada(GBTK_RETROCESO))
        {
            if(estado.cantidad_letras > 0)
            {
                estado.cantidad_letras--;
                estado.buffer[estado.cantidad_letras] = '\0';
                /// Si el cursor estaba en el boton ACEPTAR, volver al teclado
                if(estado.cursor_fila == TECLADO_FILAS)
                    estado.cursor_fila = TECLADO_FILAS - 1;
            }
        }
    }

    /// Copiar resultado al buffer del llamador
    strncpy(nombre_destino, estado.buffer, NOMBRE_MAX_CHARS);
    nombre_destino[NOMBRE_MAX_CHARS] = '\0';
}
