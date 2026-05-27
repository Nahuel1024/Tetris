/**
 * @file pagina_menu.c
 * @brief Implementacion de la pagina del menu principal.
 *
 * Reemplaza menu.c y fuentes.c. Usa FUENTE_MENU_8x8 del modulo fuente.c
 * y dibujar_rectangulo() de primitivas.c. Todos los tamanios escalan
 * con el layout igual que el resto del proyecto.
 */

#include "pagina_menu.h"
#include "GBT/gbt_entrada.h"
#include "paletacolor.h"

/* ========================================================================== */
/* HELPERS DE GEOMETRIA                                                       */
/* ========================================================================== */

static int boton_ancho(const t_layout *l)
{
    return (int)(MENU_BOTON_ANCHO_BASE * l->escala_pantalla);
}

static int boton_alto(const t_layout *l)
{
    return (int)(MENU_BOTON_ALTO_BASE * l->escala_pantalla);
}

static int separacion(const t_layout *l)
{
    return (int)(MENU_SEPARACION_BASE * l->escala_pantalla);
}

/* ========================================================================== */
/* LOGICA                                                                     */
/* ========================================================================== */

void pagina_menu_inicializar(t_menu *menu)
{
    menu->seleccion_actual  = MENU_BOTON_JUGAR;
    menu->opcion_elegida    = 0;
    menu->cantidad_opciones = MENU_CANT_OPCIONES;
}

int pagina_menu_actualizar(t_menu *menu)
{
    if(gbt_tecla_presionada(GBTK_ABAJO))
    {
        menu->seleccion_actual++;
        if(menu->seleccion_actual > menu->cantidad_opciones)
            menu->seleccion_actual = 1;
    }

    if(gbt_tecla_presionada(GBTK_ARRIBA))
    {
        menu->seleccion_actual--;
        if(menu->seleccion_actual < 1)
            menu->seleccion_actual = menu->cantidad_opciones;
    }

    if(gbt_tecla_presionada(GBTK_ENTER))
        menu->opcion_elegida = menu->seleccion_actual;

    return menu->opcion_elegida;
}

/* ========================================================================== */
/* RENDERIZADO                                                                */
/* ========================================================================== */

/**
 * @brief Dibuja un boton con su texto centrado.
 *
 * @param layout   Layout activo.
 * @param x        X del boton.
 * @param y        Y del boton.
 * @param texto    Texto a mostrar dentro del boton.
 * @param color    Color de fondo del boton.
 */
static void dibujar_boton(const t_layout *layout,
                           int x, int y,
                           const char *texto, int color)
{
    int bw = boton_ancho(layout);
    int bh = boton_alto(layout);

    dibujar_rectangulo(layout, x, y, bw, bh, color);

    /// Texto centrado dentro del boton
    int texto_ancho = fuente_ancho_texto(&FUENTE_MENU_8x8, layout, texto);
    int texto_alto  = fuente_alto_glifo(&FUENTE_MENU_8x8, layout);
    int texto_x     = x + (bw - texto_ancho) / 2;
    int texto_y     = y + (bh - texto_alto)  / 2;

    fuente_dibujar_texto(&FUENTE_MENU_8x8, layout,
                          texto_x, texto_y,
                          texto, MENU_COLOR_TEXTO);
}

void pagina_menu_dibujar(const t_layout *layout, const t_menu *menu, int x, int y)
{
    int sep = separacion(layout);

    dibujar_rectangulo(layout, 0, 0, layout->ancho_sistema, layout->alto_sistema, BORDE);

    dibujar_boton(layout, x, y,
                  "JUGAR",
                  menu->seleccion_actual == MENU_BOTON_JUGAR
                      ? MENU_COLOR_SELECCIONADO : MENU_COLOR_NORMAL);

    dibujar_boton(layout, x, y + sep,
                  "AJUSTES",
                  menu->seleccion_actual == MENU_BOTON_AJUSTES
                      ? MENU_COLOR_SELECCIONADO : MENU_COLOR_NORMAL);

    dibujar_boton(layout, x, y + sep * 2,
                  "SALIR",
                  menu->seleccion_actual == MENU_BOTON_SALIR
                      ? MENU_COLOR_SELECCIONADO : MENU_COLOR_NORMAL);
}
