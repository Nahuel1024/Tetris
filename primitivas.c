/**
 * @file primitivas.c
 * @brief Implementacion de las operaciones graficas base.
 */

#include "primitivas.h"

void dibujar_rectangulo(const t_layout *layout, int x, int y, int ancho, int alto, int color)
{
    (void)layout;
    for(int i = 0; i < alto; i++)
        for(int j = 0; j < ancho; j++)
            gbt_dibujar_pixel(x + j, y + i, color);
}

void dibujar_cuadrado_3d(const t_layout *layout, int x, int y, int color, int tam)
{
    const int grosor = (int)(layout->escala_pantalla + 0.5);

    /// Relleno interior
    for(int i = grosor; i < tam - grosor; i++)
        for(int j = grosor; j < tam - grosor; j++)
            gbt_dibujar_pixel(x + j, y + i, color);

    /**
     * Los bordes verticales (izquierdo y derecho) dibujan la columna completa
     * y dominan las cuatro esquinas. Los bordes horizontales (superior e inferior)
     * dibujan solo entre los bordes verticales para no pisarlos.
     *
     * Resultado con grosor=2:
     *   CL CL .. .. .. .. .. .. .. .. .. .. DR DR  ← esquinas: izq=claro, der=oscuro
     *   CL CL .. .. .. .. .. .. .. .. .. .. DR DR
     *   CL CL CL .. rr rr rr rr rr .. DR DR DR DR  ← superior claro entre verticales
     *   CL CL CL .. rr rr rr rr rr .. DR DR DR DR
     *   CL CL rr rr rr rr rr rr rr rr rr rr DR DR
     *   ...
     *   CL CL OO .. rr rr rr rr rr .. OO DR DR DR  ← inferior oscuro entre verticales
     *   CL CL OO .. rr rr rr rr rr .. OO DR DR DR
     *   CL CL .. .. .. .. .. .. .. .. .. .. DR DR
     *   CL CL .. .. .. .. .. .. .. .. .. .. DR DR
     */
    for(int g = 0; g < grosor; g++)
    {
        for(int i = 0; i < tam - grosor; i++)
        {
            gbt_dibujar_pixel(x + tam - 1 - g, y + i,   BORDE);  ///< Borde derecho
        }

        for(int i = 0; i < tam; i++)
        {
            gbt_dibujar_pixel(x + i , y + tam - 1 - g,  BORDE);  ///< Borde inferior
        }

        for(int i = 0; i < tam - 2 * grosor; i++)
        {
            gbt_dibujar_pixel(x + g, y + grosor + i,         FONDO);  ///< Borde izquierdo
        }

        for(int i = 0; i < tam - grosor; i++)
        {
            gbt_dibujar_pixel(x + i, y + g,             FONDO);  ///< Borde superior
        }
    }
}
