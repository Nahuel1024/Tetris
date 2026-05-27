/**
 * @file ajustes.c
 * @brief Implementacion de la pantalla de ajustes.
 *
 * Navegacion:
 *  - Arriba/Abajo: mueve el cursor entre opciones
 *  - Izquierda/Derecha: modifica el valor del ajuste seleccionado
 *  - Enter: confirma si el cursor esta en APLICAR o VOLVER
 */

#include "ajustes.h"
#include "juego.h"
#include "GBT/gbt_entrada.h"
#include <math.h>

/* ========================================================================== */
/* HELPERS DE GEOMETRIA                                                       */
/* ========================================================================== */

static int fila_alto(const t_layout *l)
{
    return (int)(AJUSTES_FILA_ALTO_BASE * l->escala_pantalla);
}

static int fila_sep(const t_layout *l)
{
    return (int)(AJUSTES_FILA_SEP_BASE * l->escala_pantalla);
}

static int boton_ancho(const t_layout *l)
{
    return (int)(AJUSTES_BOTON_ANCHO_BASE * l->escala_pantalla);
}

static int boton_alto(const t_layout *l)
{
    return (int)(AJUSTES_BOTON_ALTO_BASE * l->escala_pantalla);
}

static int boton_sep(const t_layout *l)
{
    return (int)(AJUSTES_BOTON_SEP_BASE * l->escala_pantalla);
}

/**
 * @brief Ancho total del panel de ajustes.
 * Calculado para que quepan etiqueta + valor en una fila.
 * Base CGA: 160px
 */
static int panel_ancho(const t_layout *l)
{
    return (int)(160 * l->escala_pantalla);
}

/**
 * @brief Alto total del panel: 2 filas de ajuste + separadores + 2 botones.
 */
static int panel_alto(const t_layout *l)
{
    return 2 * fila_alto(l)
           + 3 * fila_sep(l)
           + boton_alto(l);
}

/// X inicial del panel centrado horizontalmente
static int panel_ini_x(const t_layout *l)
{
    return (l->ancho_sistema - panel_ancho(l)) / 2;
}

/// Y inicial del panel centrado en el area visible
static int panel_ini_y(const t_layout *l)
{
    return l->margen_y + (l->alto_visible - panel_alto(l)) / 2;
}

/* ========================================================================== */
/* HELPERS DE LOGICA                                                          */
/* ========================================================================== */

/**
 * @brief Redondea un double a un decimal para evitar errores de punto flotante
 *        al comparar y mostrar la velocidad.
 */
static double redondear_velocidad(double v)
{
    return round(v * 10.0) / 10.0;
}

/**
 * @brief Convierte la velocidad a un string legible "0.X".
 *        Escribe en buf (debe tener al menos 4 bytes).
 */
static void velocidad_a_string(double v, char *buf)
{
    int decimas = (int)round(v * 10.0);
    buf[0] = '0';
    buf[1] = '.';
    buf[2] = '0' + decimas;
    buf[3] = '\0';
}

/* ========================================================================== */
/* DIBUJO DE COMPONENTES                                                      */
/* ========================================================================== */

/**
 * @brief Dibuja una fila de ajuste con etiqueta a la izquierda y valor a la derecha.
 *
 * @param layout    Layout activo.
 * @param x         X inicial de la fila.
 * @param y         Y inicial de la fila.
 * @param ancho     Ancho total de la fila.
 * @param alto      Alto de la fila.
 * @param etiqueta  Texto descriptivo del ajuste (ej: "RESOLUCION").
 * @param valor     Valor actual como string (ej: "VGA").
 * @param activa    true si el cursor esta sobre esta fila.
 */
static void dibujar_fila_ajuste(const t_layout *layout,
                                 int x, int y, int ancho, int alto,
                                 const char *etiqueta, const char *valor,
                                 bool activa)
{
    int color_fondo = activa ? AJUSTES_COLOR_FILA_ACTIVA : AJUSTES_COLOR_FILA_NORMAL;

    dibujar_rectangulo(layout, x, y, ancho, alto, color_fondo);

    /// Etiqueta: margen izquierdo de 4px base
    int margen = (int)(4 * layout->escala_pantalla);
    int texto_y = y + (alto - fuente_alto_glifo(&FUENTE_MENU_8x8, layout)) / 2;

    fuente_dibujar_texto(&FUENTE_MENU_8x8, layout,
                          x + margen, texto_y,
                          etiqueta, AJUSTES_COLOR_TEXTO);

    /// Valor: alineado a la derecha con margen
    int valor_ancho = fuente_ancho_texto(&FUENTE_MENU_8x8, layout, valor);
    fuente_dibujar_texto(&FUENTE_MENU_8x8, layout,
                          x + ancho - valor_ancho - margen, texto_y,
                          valor, AJUSTES_COLOR_VALOR);
}

/**
 * @brief Dibuja un boton de accion (APLICAR o VOLVER).
 */
static void dibujar_boton_ajuste(const t_layout *layout,
                                  int x, int y, int ancho, int alto,
                                  const char *texto, bool activo)
{
    int color_fondo = activo ? AJUSTES_COLOR_BOTON_ACTIVO : AJUSTES_COLOR_BOTON_NORMAL;

    dibujar_rectangulo(layout, x, y, ancho, alto, color_fondo);

    int texto_ancho = fuente_ancho_texto(&FUENTE_MENU_8x8, layout, texto);
    int texto_alto  = fuente_alto_glifo(&FUENTE_MENU_8x8, layout);

    fuente_dibujar_texto(&FUENTE_MENU_8x8, layout,
                          x + (ancho - texto_ancho) / 2,
                          y + (alto  - texto_alto)  / 2,
                          texto, AJUSTES_COLOR_BOTON_TEXTO);
}

void pagina_ajustes_dibujar(const t_layout *layout, const t_ajustes *ajustes)
{
    int px = panel_ini_x(layout);
    int py = panel_ini_y(layout);
    int pw = panel_ancho(layout);
    int fh = fila_alto(layout);
    int fs = fila_sep(layout);
    int bw = boton_ancho(layout);
    int bh = boton_alto(layout);
    int bs = boton_sep(layout);

    /// Fondo de la pantalla
    dibujar_rectangulo(layout, 0, layout->margen_y,
                       layout->ancho_sistema, layout->alto_visible,
                       AJUSTES_COLOR_FONDO);

    /// Titulo centrado arriba del panel
    int titulo_ancho = fuente_ancho_texto(&FUENTE_MENU_8x8, layout, "AJUSTES");
    fuente_dibujar_texto(&FUENTE_MENU_8x8, layout,
                          px + (pw - titulo_ancho) / 2,
                          py - fh,
                          "AJUSTES", AJUSTES_COLOR_TEXTO);

    /// Fila 1: Resolucion
    const char *val_res = (ajustes->resolucion == AJUSTES_RES_CGA) ? "CGA" : "VGA";
    dibujar_fila_ajuste(layout,
                         px, py, pw, fh,
                         "RESOLUCION", val_res,
                         ajustes->cursor == AJUSTES_OPC_RESOLUCION);

    /// Fila 2: Velocidad
    char val_vel[4];
    velocidad_a_string(ajustes->velocidad, val_vel);
    dibujar_fila_ajuste(layout,
                         px, py + fh + fs, pw, fh,
                         "VELOCIDAD", val_vel,
                         ajustes->cursor == AJUSTES_OPC_VELOCIDAD);

    /// Botones APLICAR y VOLVER centrados debajo de las filas
    int botones_y     = py + (fh + fs) * 2 + fs;
    int botones_total = bw * 2 + bs;
    int botones_x     = px + (pw - botones_total) / 2;

    dibujar_boton_ajuste(layout,
                          botones_x, botones_y, bw, bh,
                          "APLICAR",
                          ajustes->cursor == AJUSTES_OPC_APLICAR);

    dibujar_boton_ajuste(layout,
                          botones_x + bw + bs, botones_y, bw, bh,
                          "VOLVER",
                          ajustes->cursor == AJUSTES_OPC_VOLVER);
}

/* ========================================================================== */
/* LOGICA                                                                     */
/* ========================================================================== */

void ajustes_inicializar(t_ajustes *ajustes, int resolucion, double velocidad)
{
    ajustes->resolucion          = resolucion;
    ajustes->velocidad           = redondear_velocidad(velocidad);
    ajustes->resolucion_original = resolucion;
    ajustes->velocidad_original  = redondear_velocidad(velocidad);
    ajustes->cursor              = AJUSTES_OPC_RESOLUCION;
}

int pagina_ajustes_ejecutar(t_layout *layout, t_ajustes *ajustes,
                             const t_tablero *tablero)
{
    while(1)
    {
        gbt_borrar_backbuffer(0);
        pagina_ajustes_dibujar(layout, ajustes);
        gbt_volcar_backbuffer();

        gbt_procesar_entrada();

        /// --- Navegacion vertical ---
        if(gbt_tecla_presionada(GBTK_ABAJO))
        {
            ajustes->cursor++;
            if(ajustes->cursor > AJUSTES_CANT_OPCIONES)
                ajustes->cursor = 1;
        }

        if(gbt_tecla_presionada(GBTK_ARRIBA))
        {
            ajustes->cursor--;
            if(ajustes->cursor < 1)
                ajustes->cursor = AJUSTES_CANT_OPCIONES;
        }

        /// --- Modificacion de valores (solo en filas de ajuste) ---
        if(ajustes->cursor == AJUSTES_OPC_RESOLUCION)
        {
            if(gbt_tecla_presionada(GBTK_IZQUIERDA) || gbt_tecla_presionada(GBTK_DERECHA))
                ajustes->resolucion = (ajustes->resolucion == AJUSTES_RES_CGA)
                                      ? AJUSTES_RES_VGA
                                      : AJUSTES_RES_CGA;
        }

        if(ajustes->cursor == AJUSTES_OPC_VELOCIDAD)
        {
            if(gbt_tecla_presionada(GBTK_DERECHA))
            {
                double nueva = redondear_velocidad(ajustes->velocidad + AJUSTES_VEL_PASO);
                if(nueva <= AJUSTES_VEL_MAX)
                    ajustes->velocidad = nueva;
            }

            if(gbt_tecla_presionada(GBTK_IZQUIERDA))
            {
                double nueva = redondear_velocidad(ajustes->velocidad - AJUSTES_VEL_PASO);
                if(nueva >= AJUSTES_VEL_MIN)
                    ajustes->velocidad = nueva;
            }
        }

        /// --- Confirmacion ---
        if(gbt_tecla_presionada(GBTK_ENTER))
        {
            if(ajustes->cursor == AJUSTES_OPC_APLICAR)
            {
                /// Si cambio la resolucion, recrear la ventana y recalcular el layout
                if(ajustes->resolucion != ajustes->resolucion_original)
                {
                    gbt_destruir_ventana();
                    iniciar_pantalla(layout, ajustes->resolucion, tablero);
                    ajustes->resolucion_original = ajustes->resolucion;
                }
                return AJUSTES_APLICAR;
            }

            if(ajustes->cursor == AJUSTES_OPC_VOLVER)
            {
                /// Descartar cambios restaurando los valores originales
                ajustes->resolucion = ajustes->resolucion_original;
                ajustes->velocidad  = ajustes->velocidad_original;
                return AJUSTES_VOLVER;
            }
        }
    }
}
