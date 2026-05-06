#ifndef COLORES_H
#define COLORES_H
#include "GBT/gbt_graficos.h"

// Cantidad total de colores que nuestra paleta va a manejar.
#define CANT_COLORES 16

// Estos defines son "Índices". Mapean un nombre amigable a una posición
// dentro de la paleta. Por ejemplo, cuando pasas 'FONDO' (0) a dibujar_pixel,
// usa el color en la posición 0 del array 'paleta'.
#define BORDE 2
#define INTERFAZ 1
#define FONDO 0

// Índices de colores para cada forma de pieza del Tetris.
// Además, la forma de la pieza en la matriz de `tetrominos` está rellena con estos mismos números.
#define I 3
#define O 4
#define T 5
#define S 6
#define L 7
#define J 8
#define Z 9

// Extern permite avisarle a otros archivos que la variable 'paleta'
// existe, pero está definida e inicializada en otro archivo (.c).
extern tGBT_ColorRGB paleta[CANT_COLORES];

#endif
