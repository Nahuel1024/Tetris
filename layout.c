/**
 * @file layout.c
 * @brief Implementacion del calculo de layout de pantalla.
 */

#include "layout.h"

void layout_calcular(t_layout *layout,  int ancho_sis, int alto_sis, double escala,
                          int margen, const t_tablero *tablero)
{
    layout->ancho_sistema   = ancho_sis;
    layout->alto_sistema    = alto_sis;
    layout->escala_pantalla = escala;
    layout->margen_y        = margen;
    layout->alto_visible    = alto_sis - margen * 2;
    layout->tam_celda       = (int)(TAM_CELDA_BASE * escala);

    int ancho_tablero        = tablero->dimensiones.ancho * layout->tam_celda;
    int alto_tablero_visible = (tablero->dimensiones.alto - FILAS_SPAWN) * layout->tam_celda;

    layout->ancho_tablero      = ancho_tablero;
    layout->margen_horizontal  = (ancho_sis - ancho_tablero) / 2;
    layout->margen_vertical    = layout->margen_y + (layout->alto_visible - alto_tablero_visible) / 2;
}
