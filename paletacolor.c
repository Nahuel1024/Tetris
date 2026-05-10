/**
 * @file paletacolor.c
 * @brief Implementación física de la paleta de colores del juego en formato RGB.
 */

#include "paletacolor.h"

/* ========================================================================== */
/* DEFINICIÓN DE LA PALETA DE COLORES                                         */
/* ========================================================================== */

/**
 * COMPLEJO: Mapeo de Colores Hexadecimales (Formato RGB 888)
 * Cada elemento del arreglo es una estructura {R, G, B} donde cada canal
 * de color va de 0x00 (0) a 0xFF (255) en valores hexadecimales.
 * * ¡ATENCIÓN! El orden físico de este arreglo es estrictamente dependiente
 * de los macros (#define) establecidos en paletacolor.h. Si cambias el índice
 * en el header, debes reordenar esta lista.
 */
tGBT_ColorRGB paleta[CANT_COLORES] =
{
    /* --- Colores de Tetrominos (Índices 0 a 6) --- */
    {0x00, 0xC8, 0xFF}, // 0: I (Celeste)
    {0xFF, 0xDC, 0x00}, // 1: O (Amarillo)
    {0xB4, 0x00, 0xFF}, // 2: T (Morado)
    {0x00, 0xFF, 0x64}, // 3: S (Verde claro)
    {0xFF, 0x50, 0x00}, // 4: L (Naranja)
    {0x00, 0x64, 0xFF}, // 5: J (Azul)
    {0xFF, 0x00, 0x50}, // 6: Z (Rojo/Rosado)

    /* --- Colores de Entorno e Interfaz (Índices 7 a 9) --- */
    {0x0A, 0x0A, 0x14}, // 7: BORDE    / Fondo oscuro
    {0x28, 0x28, 0x3C}, // 8: INTERFAZ / Color de celdas vacías
    {0xC8, 0xC8, 0xC8}, // 9: FONDO    / Bloque neutro

    /* --- Colores de Reserva (Índices 10 a 14) --- */
    {0x78, 0x78, 0xFF}, // 10
    {0xFF, 0x78, 0x78}, // 11
    {0x78, 0xFF, 0x78}, // 12
    {0xFF, 0xFF, 0x78}, // 13
    {0xB4, 0xB4, 0xB4}, // 14 (Reservados para futuros usos)

    /* --- Color Especial (Índice 15) --- */
    {0xFF, 0xFF, 0xFF}  // 15: Transparente (La librería GBT usa el último índice para transparencia)
};
